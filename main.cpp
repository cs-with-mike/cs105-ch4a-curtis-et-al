#include "PureLexer.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    Lexing::PureLexer pl("../sample.tk", "../out.sample.curtis.txt");
    while (pl.next_token()->type != Lexing::T_NULL);
    Parsing::Parser p = Parsing::Parser("../sample.tk", "../nothing_here.txt");
    p.parse();
}
