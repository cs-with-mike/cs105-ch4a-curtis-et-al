//
// Created by Joshua Nielsen on 10/5/23.
//

#include "Lexer.h"

#include <utility>

Lexer::Lexer(const std::string &read_file_name) {
    this->reader = std::ifstream(read_file_name);
    this->t_buffer = std::make_shared<Token>();
    this->t_buffer->type = T_NULL;
}

std::shared_ptr<Token> Lexer::next_token() {
    if (this->t_buffer->type != T_NULL) {
        auto return_val = std::shared_ptr<Token>(this->t_buffer);
        this->t_buffer = std::make_shared<Token>();
        this->t_buffer->type = T_NULL;
        return return_val;
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
    return std::shared_ptr<Token>(this->t_buffer);
}

std::shared_ptr<Token> Lexer::peek_token() {
    if (this->t_buffer->type == T_NULL) {
        return std::shared_ptr<Token>(this->next_token());
    } else {
        return std::shared_ptr<Token>(this->t_buffer);
    }
}
