#include <iostream>
#include <fstream>
#include <cctype>

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
    std::str lexstr = lexeme.str();
    static std::string types[] = {"INT_LIT    ", "IDENT    ", "ASSIGN_OP  ", "ADD_OP     ", "SUB_OP     ", "MULT_OP     ", "DIV_OP     ", "LEFT_PAREN ", "RIGHT_PAREN"};
    static std::string token_dec = "Next token is:";
    static std::string lexem_dec = " | Next lexeme is ";
    writer->write(lexstr->c_str(), lexstr->length);
}

int main(int argc, char *argv[]) {
    std::ifstream *reader;
    std::stringstream char_buffer;
    char c;

    // Define states for our finite state machine
    states state = OUTSIDE;

    // Make sure that the file provided could actually be read
    if (!(reader = open_file(argc, argv))) {
        std::cout << "Program terminating" << std::endl;
        return 1;
    }
    
    // Finite state machine for parsing begins with iterating over every char in file
    while (true) {
        c = reader->get();
        if (reader->rdstate() & std::ios_base::eofbit) {
            break;  // If we hit eof char, we are done
        }
        switch (state) {
            case OUTSIDE:
                break;
            case INTEGER:
                if (isalpha(c)) {
                    lexeme_out(&char_buffer, INT, ); //TODO: File to write to
                    char_buffer.str("");
                    char_buffer << c;
                    state = IDENTIFIER;
                }
                else if (isdigit(c)) {
                    char_buffer << c;
                }
                else if ((c <= '(' && c >= '/') || c == '=') {
                    lexeme_out(&char_buffer, INT, ); //TODO: File to write to
                    char_buffer.str("");
                    char_buffer << c;

                    if (c == '(') {
                        lexeme_out(&char_buffer, LEFT_PAREN, ); //TODO: File to write to
                        char_buffer.str("");
                        state = OUTSIDE;
                    }
                    else  if (c == ')') {
                        lexeme_out(&char_buffer, RIGHT_PAREN, ); //TODO: File to write to
                        char_buffer.str("");
                        state = OUTSIDE;
                    }
                    else  if (c == '*') {
                        lexeme_out(&char_buffer, MULT_OP, ); //TODO: File to write to
                        char_buffer.str("");
                        state = OUTSIDE;
                    }
                }
                else{
                    lexeme_out(&char_buffer, INT, ); //TODO: File to write to
                    char_buffer.str("");
                    state = OUTSIDE;
                }
            case IDENTIFIER:
                break;
        }
    }

    std::cout << "Parsing complete" << std::endl;
}

