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

void Parser::out_error(Token token) {
    this->writer->write("Error - invalid tokki syntax at: ", 33);
    this->writer->write(token.value.c_str(), token.value.length());
    this->writer->write("\n", 1);
    this->writer->close();
    this->lexer->close();
    exit(-1);
}
