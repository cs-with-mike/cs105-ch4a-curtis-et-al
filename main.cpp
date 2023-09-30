#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>

enum states {OUTSIDE, INTEGER, IDENTIFIER};
enum ltypes {INT, IDT, ASN, ADD, SUB, MUL, DIV, LPR, RPR};

std::ifstream *open_file(int argc, char *argv[]) {
    std::ifstream *reader;

     // Make sure that the correct number of arguments is provided to our program
    switch (argc) {
        case 2:
            std::cout << "Filename received" << std::endl;
            break;
        default:
            std::cout << "This program takes one argument which is a filename." << std::endl;
            return nullptr;
    }

    // Create a in file stream object to read the file and attempt to open the file
    reader = new std::ifstream();
    reader->open(argv[1]);
    if (reader->rdstate() & std::ios_base::failbit) {
        std::cout << "File could not be opened. Please enter a valid file." << std::endl;
        return nullptr;
    } else {
        std::cout << "Parsing file..." << std::endl;
    }
    return reader;
}

void lexeme_out(std::stringstream *lexeme, ltypes ltype, std::ofstream *writer) {
    static std::string types[] = {
        "     INT_LIT",
        "       IDENT",
        "   ASSIGN_OP",
        "      ADD_OP",
        "      SUB_OP",
        "     MULT_OP",
        "      DIV_OP",
        "  LEFT_PAREN",
        " RIGHT_PAREN",
    };
    char token_dec[] = "Next token is:";
    char lexem_dec[] = " | Next lexeme is ";
    char newline[] = "\n";
    std::string lexstr = lexeme->str();
    writer->write(token_dec, 14);
    writer->write(types[ltype].c_str(), 12);
    writer->write(lexem_dec, 18);
    writer->write(lexstr.c_str(), lexstr.length());
    writer->write(newline, 1);
}

int main(int argc, char *argv[]) {
    states state = OUTSIDE;
    std::ofstream writer;
    std::ifstream *reader;
    std::stringstream char_buffer("");
    char c;

    //Array of ltypes
    ltypes op_lookup[62];
    op_lookup['('] = LPR;
    op_lookup[')'] = RPR;
    op_lookup['*'] = MUL;
    op_lookup['+'] = ADD;
    op_lookup['-'] = SUB;
    op_lookup['/'] = DIV;
    op_lookup['='] = ASN;

    // Make sure that the file provided could actually be read
    if (!(reader = open_file(argc, argv))) {
        std::cout << "Program terminating" << std::endl;
        return 1;
    }

    // Open a file to be written to
    writer.open("out.txt");
    std::cout << "Opening write file" << std::endl;

    // Finite state machine for parsing begins with iterating over every char in file
    while (true) {
        c = reader->get();
        if (reader->rdstate() & std::ios_base::eofbit) {
            break;  // If we hit eof char, we are done
        }
        switch (state) {
            case OUTSIDE:
                if (isblank(c)){
                } else if (isalpha(c)) {
                    char_buffer << c;
                    state = IDENTIFIER;
                } else if (isdigit(c)) {
                    char_buffer << c;
                    state = INTEGER;
                } else {
                    char_buffer << c;
                    lexeme_out(&char_buffer, op_lookup[c], &writer);
                    char_buffer.str("");
                }
                break;
            case INTEGER:
                if (isalpha(c)) {
                    lexeme_out(&char_buffer, INT, &writer);
                    char_buffer.str("");
                    char_buffer << c;
                    state = IDENTIFIER;
                }
                else if (isdigit(c)) {
                    char_buffer << c;
                }
                else if ((c >= '(' && c <= '/') || c == '=') {
                    lexeme_out(&char_buffer, INT, &writer);
                    char_buffer.str("");
                    char_buffer << c;
                    lexeme_out(&char_buffer, op_lookup[c], &writer);
                    char_buffer.str("");
                    state = OUTSIDE;
                }
                else{
                    lexeme_out(&char_buffer, INT, &writer);
                    char_buffer.str("");
                    state = OUTSIDE;
                }
                break;
            case IDENTIFIER:
                if (isalpha(c) || isdigit(c)) {
                    char_buffer << c;
                }
                else if ((c >= '(' && c <= '/') || c == '=') {
                    lexeme_out(&char_buffer, IDT, &writer);
                    char_buffer.str("");
                    char_buffer << c;
                    lexeme_out(&char_buffer, op_lookup[c], &writer);
                    char_buffer.str("");
                    state = OUTSIDE;
                }
                else{
                    lexeme_out(&char_buffer, IDT, &writer);
                    char_buffer.str("");
                    state = OUTSIDE;
                }
                break;
        }
    }
    
    switch (state) {
        case INTEGER:
            lexeme_out(&char_buffer, INT, &writer);
            break;
        case IDENTIFIER:
            lexeme_out(&char_buffer, IDT, &writer);
            break;
    }
    char ending[] = "Next token is:         EOF | Next lexeme is EOF\n";
    writer.write(ending, 48);

    std::cout << "Parsing complete" << std::endl;
    std::cout << "Closing write file" << std::endl;
    writer.close();
}

