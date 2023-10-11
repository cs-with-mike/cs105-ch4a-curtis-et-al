//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_LEXER_H
#define CS_105_CH4A_CURTIS_ET_AL_LEXER_H

#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <memory>

namespace Lexing {
    enum token_type {T_INT, T_IDENT, T_ASSIGN, T_ADD, T_SUB, T_MUL, T_DIV, T_LPAREN, T_RPAREN, T_NULL};

    struct token {
        std::string value;
        token_type type;
    };

    typedef struct token Token;

    class Lexer {
    public:
        Lexer();
        explicit Lexer(const std::string &read_fname);
        virtual ~Lexer()=default;
        virtual std::shared_ptr<Token> next_token();
        virtual std::shared_ptr<Token> peek_token();

    protected:
        void fill_buffer();
        virtual void gen_t_hook();
        virtual void next_t_hook();
        virtual void peek_t_hook();

        std::shared_ptr<Token> t_buffer;
        std::ifstream reader;
        bool buffer_full=false;
    };
}

#endif //CS_105_CH4A_CURTIS_ET_AL_LEXER_H
