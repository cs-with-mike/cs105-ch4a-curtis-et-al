//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_LEXER_H
#define CS_105_CH4A_CURTIS_ET_AL_LEXER_H

#include <string>
#include <fstream>
#include <cctype>
#include <sstream>

enum ltypes {INT, IDT, ASN, ADD, SUB, MUL, DIV, LPR, RPR};

typedef struct{
    std::string value;
    ltypes type;
} Token;

class Lexer {
    public:
        Lexer(char file_name[]);
        Token next_token();

    private:
        std::ifstream *reader;
};


#endif //CS_105_CH4A_CURTIS_ET_AL_LEXER_H
