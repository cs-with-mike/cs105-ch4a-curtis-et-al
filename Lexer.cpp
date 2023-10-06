//
// Created by Joshua Nielsen on 10/5/23.
//

#include "Lexer.h"

Lexer::Lexer(char file_name[]){
    this->reader = new std::ifstream();
    this->reader->open(file_name);
};

Token Lexer::next_token() {

}
