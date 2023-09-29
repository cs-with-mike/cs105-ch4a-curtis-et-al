#include <iostream>
#include <fstream>

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

int main(int argc, char *argv[]) {
    std::ifstream *reader;
    char c;

    // Define states for our finite state machine
    enum states {OUTSIDE, INT, IDENT};
    states state = OUTSIDE;

    // Make sure that the file provided could actually be read
    if (!(reader = open_file(argc, argv))) {
        std::cout << "Program terminating" << std::endl;
        return 1;
    }
    
    while ((c = reader->get()) != EOF) {
        switch (state) {
            case OUTSIDE:
                break;
            case INT:
                break;
            case IDENT:
                break;
        }
    }
}

