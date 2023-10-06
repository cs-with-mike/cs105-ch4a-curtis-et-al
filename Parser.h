//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_PARSER_H
#define CS_105_CH4A_CURTIS_ET_AL_PARSER_H

#include "Lexer.h" //import the header file which comes with all the variables we'd need from the lexer.
#include <fstream> //import this to work with files

enum nonterminals {EXPRESSION, TERM, FACTOR};

class Parser {
    public:
        Parser(Lexer *lexer, char filename[]);
        void expression(int depth);

    private:
        Lexer *lexer;
        std::ofstream *writer;
        void term(int depth);
        void factor(int depth);
        void out_token(int depth, Token);
        void out_nonterminal(int depth, nonterminals nt);
        void out_error(Token token);
};


#endif //CS_105_CH4A_CURTIS_ET_AL_PARSER_H
