#include "PureLexer.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    Lexing::PureLexer pl("../sample.tk", "../curtis.lexer.sample.txt");
    while (pl.next_token()->type != Lexing::T_NULL);
    Parsing::Parser p = Parsing::Parser("../sample.tk", "../curtis.parser.sample.txt");
    p.parse();
}
