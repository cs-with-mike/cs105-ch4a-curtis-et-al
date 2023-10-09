//
// Created by Joshua Nielsen on 10/5/23.
//

#include <utility>

#include "Lexer.h"

Lexer::Lexer() {
    this->t_buffer = std::make_shared<Token>();  // smart ptr init to nullptr, so we need to manually create new Token
    this->t_buffer->type = T_NULL;  // Token->type inits to T_INT, so we need to manually set to T_NULL
}

Lexer::Lexer(const std::string &read_file_name) {
    this->reader.open(read_file_name);  // reader init to ifstream unopened, so we can just open it
    this->t_buffer = std::make_shared<Token>();  // smart ptr init to nullptr, so we manually create new Token
    this->t_buffer->type = T_NULL;  // Token->type inits to T_INT, so we need to manually set to T_NULL
    this->is_open = true;  // is_open I think is just uninitialized data, so we initialize it? TODO: check this one
}

int Lexer::open(const std::string &read_file_name) {
    if (this->is_open) {
        return 1;  // Lexer has already opened a file
    } else {
        this->reader.open(read_file_name);  // It is impossible for Lexer to have uninit reader, so we safely open
        this->is_open = true;  // Set open status to true so it cannot be opened again
        return 0;
    }
}

std::shared_ptr<Token> Lexer::next_token() {
    if (this->t_buffer->type != T_NULL) {  // If we've already peeked and there is a token ready to go
        auto return_val = std::move(this->t_buffer); // We can move b/c we dispose of t_buffer soon
        this->t_buffer = std::make_shared<Token>();
        this->t_buffer->type = T_NULL;
        return return_val;  // Have to construct new shared_ptr when returning
    }

    std::stringstream buffer("");
    char c = EOF;

    this->reader >> c;  // get first non whitespace char
    buffer << c;  // and put it in the string buffer

    switch (c) {
        case EOF:  // at end of file
            this->t_buffer->type = T_NULL;
            break;
        case '+':
            this->t_buffer->type = T_ADD;
            break;
        case '-':
            this->t_buffer->type = T_SUB;
            break;
        case '*':
            this->t_buffer->type = T_MUL;
            break;
        case '/':
            this->t_buffer->type = T_DIV;
            break;
        case '(':
            this->t_buffer->type = T_LPAREN;
            break;
        case ')':
            this->t_buffer->type = T_RPAREN;
            break;
        case '=':
            this->t_buffer->type = T_ASSIGN;
            break;
        default:
            if (isalnum(c)) {
                while(this->reader.get(c)) {
                    if (isalpha(c)) {
                        buffer << c;
                    } else {
                        this->reader.unget();
                        break;
                    }
                }
                this->t_buffer->type = T_IDENT;
            } else if (isnumber(c)) {
                while(this->reader.get(c)) {
                    if (isnumber(c)) {
                        buffer << c;
                    } else {
                        this->reader.unget();
                        break;
                    }
                }
                this->t_buffer->type = T_INT;
            } else {
                this->t_buffer->type = T_NULL;
            }
    }
    this->t_buffer->value = buffer.str();
    this->token_hook();
    return this->t_buffer;
}

std::shared_ptr<Token> Lexer::peek_token() {
    if (this->t_buffer->type == T_NULL) {
        return this->next_token();
    } else {
        return this->t_buffer;
    }
}
