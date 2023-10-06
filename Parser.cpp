//
// Created by Joshua Nielsen on 10/5/23.
//

#include "Parser.h"

Parser::Parser(Lexer *lexer, char *filename) {
    this->lexer = lexer;
    this->writer = new std::ofstream();
    this->writer->open(filename);
}

void Parser::term(int depth) {
    Token t;
    this->factor(depth +1);
    t = this->lexer->peak_token();
    while ((t.type == MUL) || (t.type == DIV)){
        out_token(depth, this->lexer->next_token());
        this->factor(depth +1);
    }
}
