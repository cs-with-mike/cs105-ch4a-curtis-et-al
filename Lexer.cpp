//
// Created by Joshua Nielsen on 10/5/23.
//

#include <utility>

#include "Lexer.h"

namespace Lexing {
    Lexer::Lexer() {
        this->t_buffer = std::make_shared<Token>();  // smart ptr init to nullptr, so we need to manually create new Token
        this->t_buffer->type = T_NULL;  // Token->type inits to T_INT, so we need to manually set to T_NULL
    }

    Lexer::Lexer(const std::string &read_fname) {
        this->reader.open(read_fname);  // reader init to ifstream unopened, so we can just open it
        this->t_buffer = std::make_shared<Token>();  // smart ptr init to nullptr, so we manually create new Token
        this->t_buffer->type = T_NULL;  // Token->type inits to T_INT, so we need to manually set to T_NULL
    }

    std::shared_ptr<Token> Lexer::next_token() {
        if (!this->buffer_full) {
            this->fill_buffer();
        }
        this->buffer_full = false;
        this->next_t_hook();
        return std::move(this->t_buffer);  // Can move because we no longer need it
    }

    std::shared_ptr<Token> Lexer::peek_token() {
        if (!this->buffer_full) {
            this->fill_buffer();
        }
        this->peek_t_hook();
        return this->t_buffer;
    }

    void Lexer::fill_buffer() {
        std::stringstream buffer("");
        char c = EOF;
        this->t_buffer = std::make_shared<Token>();  // generate new Token

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
                if (isalpha(c)) {
                    while(this->reader.get(c)) {
                        if (isalnum(c)) {
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
        this->buffer_full = true;
        this->gen_t_hook();
    }

    void Lexer::gen_t_hook() {}

    void Lexer::next_t_hook() {}

    void Lexer::peek_t_hook() {}
}
