//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_PARSER_H
#define CS_105_CH4A_CURTIS_ET_AL_PARSER_H

#include "Lexer.h" //import the header file which comes with all the variables we'd need from the lexer.
#include <fstream> //import this to work with files

class Parser {
    public:
        Parser(Lexer *lexer, char filename[]);

    private:
        Lexer *lexer;
        std::ofstream *writer;
};


#endif //CS_105_CH4A_CURTIS_ET_AL_PARSER_H
