//
// Created by Joshua Nielsen on 10/5/23.
//

#include "Lexer.h"

#include <utility>

Lexer::Lexer(const std::string &read_file_name) {
    this->reader = std::ifstream(read_file_name);
}

Token Lexer::next_token() {
    std::stringstream buffer("");
    char c = EOF;

    this->reader >> c;  // get first non whitespace char
    buffer << c;  // and put it in the string buffer

    switch (c) {
        case EOF:  // at end of file
            this->current_token.type = T_NULL;
            break;
        case '+':
            this->current_token.type = T_ADD;
            break;
        case '-':
            this->current_token.type = T_SUB;
            break;
        case '*':
            this->current_token.type = T_MUL;
            break;
        case '/':
            this->current_token.type = T_DIV;
            break;
        case '(':
            this->current_token.type = T_LPAREN;
            break;
        case ')':
            this->current_token.type = T_RPAREN;
            break;
        case '=':
            this->current_token.type = T_ASSIGN;
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
                this->current_token.type = T_IDENT;
            } else if (isnumber(c)) {
                while(this->reader.get(c)) {
                    if (isnumber(c)) {
                        buffer << c;
                    } else {
                        this->reader.unget();
                        break;
                    }
                }
                this->current_token.type = T_INT;
            } else {
                this->current_token.type = T_NULL;
            }
    }
    this->current_token.value = std::move(buffer.str());
    this->token_hook();
    return this->current_token;
}

Token Lexer::peek_token() {
    return this->current_token;
}
