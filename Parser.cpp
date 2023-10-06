//
// Created by Joshua Nielsen on 10/5/23.
//

#include "Parser.h"

Parser::Parser(Lexer *lexer, char *filename) {
    this->lexer = lexer;
    this->writer = new std::ofstream();
    this->writer->open(filename);
}
