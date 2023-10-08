//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_LEXER_H
#define CS_105_CH4A_CURTIS_ET_AL_LEXER_H

#include <string>
#include <fstream>
#include <cctype>
#include <sstream>

enum token_type {T_INT, T_IDENT, T_ASSIGN, T_ADD, T_SUB, T_MUL, T_DIV, T_LPAREN, T_RPAREN, T_NULL};

typedef struct {
    std::string value;
    token_type type;
} Token;

class Lexer {
public:
    explicit Lexer(const std::string &read_file_name);
    Token next_token();
    Token peek_token();
    virtual void token_hook()=0;

protected:
    Token current_token;

private:
    std::ifstream reader;
};


#endif //CS_105_CH4A_CURTIS_ET_AL_LEXER_H
