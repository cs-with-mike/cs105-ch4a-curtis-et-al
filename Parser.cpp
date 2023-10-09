//
// Created by Joshua Nielsen on 10/5/23.
//

#include "Parser.h"

std::string Parser::mapping[] = {"INT_LIT", "IDENT", "ASSIGN_OP", "ADD_OP", "SUB_OP", "MULT_OP", "DIV_OP", "LEFT_PAREN", "RIGHT_PAREN"};
std::string Parser::nonterminalmapping[] = {"expr", "term", "factor"};

Parser::Parser(const std::string& read_file_name, const std::string& write_file_name) {
    this->writer.open(write_file_name);
    this->lexer = Parser::ParserLexer(read_file_name, &this->writer, this);
}

void Parser::expression() {
    out_nonterminal(EXPRESSION, ENT);
    this->term(); // given that an expression is going to start with a term, we can dive right into the term.
    while(this->lexer.peek_token()->type == T_ADD || this->lexer.peek_token()->type == T_SUB) {
        out_token(this->lexer.next_token());
        this->term(); // go inside the next term
    }

    out_nonterminal(EXPRESSION, EXT);
}

void Parser::term() {
    out_nonterminal(TERM, ENT);
    this->factor();
    while ((this->lexer.peek_token()->type == T_MUL) || (this->lexer.peek_token()->type == T_DIV)){
        out_token(this->lexer.next_token());
        this->factor();
    }
    out_nonterminal(TERM, EXT);
}

void Parser::factor() {
    out_nonterminal(FACTOR, ENT);
    switch (this->lexer.peek_token()->type) {
        case T_IDENT:
        case T_INT:
            out_token(this->lexer.next_token());
            break;
        case T_LPAREN:
            out_token(this->lexer.next_token());
            this->expression();
            if (this->lexer.peek_token()->type == T_RPAREN) {
                out_token(this->lexer.next_token());
            } else {
                this->out_error(this->lexer.peek_token());
            }
            break;
        default:
            this->out_error(this->lexer.peek_token());
    }
    out_nonterminal(FACTOR, EXT);
}

void Parser::out_error(const std::shared_ptr<Token> &token) {
    this->writer.write("Error - invalid tokki syntax at: ", 33);
    this->writer.write(token->value.c_str(), token->value.length());
    this->writer.write("\n", 1);
    this->writer.close();
    delete &this->lexer;
    exit(-1);  // TODO: I don't know, but not this
}

void Parser::out_token(const std::shared_ptr<Token> &token) {
    this->writer.write(std::string(this->depth, '=').c_str(), this->depth);
    writer.write(" ", 1);
    writer.write(mapping[token->type].c_str(), mapping[token->type].length());
    writer.write(" [ ", 3);
    writer.write(token->value.c_str(), token->value.length());
    writer.write("]\n", 2);
}

void Parser::out_nonterminal(nonterminals nt, front_door fd) {
    if (fd == ENT) {this->depth++;}

    char indent = (fd == ENT) ? '>' : '<';
    writer.write(std::string(this->depth, indent).c_str(), this->depth);
    writer.write(" ", 1);
    writer.write(nonterminalmapping[nt].c_str(), nonterminalmapping[nt].length());
    writer.write("\n", 1);

    if (fd == EXT) {this->depth--;}
}

void Parser::parse() {
    this->expression();
}

Parser::ParserLexer::ParserLexer(const std::string &read_file_name, std::ofstream *write_file, Parser *outer) : Lexer(read_file_name) {
    this->writer = write_file;
    this->outer = outer;
}

void Parser::ParserLexer::token_hook() {
    this->writer->write("OHHH YEAH BABYYYYY\n", 19);
}

Parser::ParserLexer &Parser::ParserLexer::operator=(Parser::ParserLexer &&b) noexcept {
    this->t_buffer = std::move(b.t_buffer);
    this->reader = std::move(b.reader);
    this->outer = b.outer;
    this->writer = b.writer;

    return *this;
}

Parser::ParserLexer::ParserLexer() : Lexer() {
    this->outer = nullptr;
    this->writer = nullptr;
}
