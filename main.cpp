//#include "PureLexer.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
//    PureLexer p("../sample.tk", "../out.sample.curtis.txt");
//    while (p.next_token()->type != T_NULL);
    Parser p = Parser("../sample.tk", "../nothing_here.txt");
    p.parse();
}
