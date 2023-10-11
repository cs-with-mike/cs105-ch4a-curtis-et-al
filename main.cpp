#include "PureLexer.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    std::string source;
    std::string lexer_out = "/dev/null";
    std::string parser_out = "/dev/null";

    if (argc != 4) {
        std::printf("tokkis requires exactly 3 arguments\n");
        return 1;
    }
    source = std::string(argv[2]);
    switch (*(argv[1])) {
        case 'l':
            lexer_out = std::string(argv[3]);
            break;
        case 'p':
            parser_out = std::string(argv[3]);
            break;
        default:
            std::printf("unrecognized argument %s\n", argv[1]);
            return 1;
    }

    Lexing::PureLexer pl(source, lexer_out);
    Parsing::Parser p = Parsing::Parser(source, parser_out);

    switch (*(argv[1])) {
        case 'l':
            while (pl.next_token()->type != Lexing::T_NULL);
            break;
        case 'p':
            p.parse();
            break;
    }
    return 0;
}
