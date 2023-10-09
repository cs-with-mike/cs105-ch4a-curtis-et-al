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

struct token {
    std::string value;
    token_type type;
};

typedef struct token Token;

class Lexer {
public:
    Lexer();
    explicit Lexer(const std::string &read_file_name);
    virtual ~Lexer()=default;
    std::shared_ptr<Token> next_token();
    std::shared_ptr<Token> peek_token();
    virtual void token_hook()=0;
    int open(const std::string &read_file_name);

protected:
    std::shared_ptr<Token> t_buffer;
    std::ifstream reader;
    bool is_open=false;
};

#endif //CS_105_CH4A_CURTIS_ET_AL_LEXER_H
