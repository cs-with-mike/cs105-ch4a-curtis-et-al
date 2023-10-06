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
    out_nonterminal(depth, TERM, ENT);
    this->factor(depth +1);
    t = this->lexer->peek_token();
    while ((t.type == MUL) || (t.type == DIV)){
        out_token(depth, this->lexer->next_token());
        this->factor(depth +1);
    }
    out_nonterminal(depth, TERM, EXT);
}

void Parser::out_error(Token token) {
    this->writer->write("Error - invalid tokki syntax at: ", 33);
    this->writer->write(token.value.c_str(), token.value.length());
    this->writer->write("\n", 1);
    this->writer->close();
    this->lexer->close();
    exit(-1);
}

void Parser::expression(int depth) {
    out_nonterminal(depth, EXPRESSION, ENT);
    this->term(depth + 1); //given that an expression is going to start with a term, we can dive right into the term.
    while(this->lexer->peek_token().type == ADD || this->lexer->peek_token().type == SUB){
        out_token(depth, this->lexer->next_token());
        this->term(depth + 1); //go inside the next term
    }

    out_nonterminal(depth, EXPRESSION, EXT);
}

void Parser::factor(int depth) {
    out_nonterminal(depth, FACTOR, ENT);
    if(this->lexer->peek_token().type == IDT){
        out_token(depth, this->lexer->next_token());
    }
    else if(this->lexer->peek_token().type == INT){
        out_token(depth, this->lexer->next_token());
    }
    else{
        if(this->lexer->peek_token().type == LPR){
            out_token(depth, this->lexer->next_token());
            this->expression(depth + 1);
            out_token(depth, this->lexer->next_token());
        }
    }
    out_nonterminal(depth, FACTOR, EXT);
}

void Parser::out_token(int depth, Token token) {
    for(int i = 0; i < depth; i++) {
        writer->write("=", 1);
    }
    writer->write(" ", 1);
    writer->write(mapping[token.type].c_str(), mapping[token.type].length());
    writer->write(" [ ", 1);
    writer->write(token.value.c_str(), token.value.length());
    writer->write("] \n", 1);
}

void Parser::out_nonterminal(int depth, nonterminals nt, front_door fd) {
    if(fd == ENT){
        for(int i = 0; i < depth; i++) {
            writer->write(">", 1);
        }
        writer->write(" ", 1);
        writer->write(nonterminalmapping[nt].c_str(), nonterminalmapping[nt].length());
        writer->write("\n", 1);
    }
    else if(fd == EXT){
        for(int i = 0; i < depth; i++) {
            writer->write("<", 1);
        }
        writer->write(" ", 1);
        writer->write(nonterminalmapping[nt].c_str(), nonterminalmapping[nt].length());
        writer->write("\n", 1);
    }
}
