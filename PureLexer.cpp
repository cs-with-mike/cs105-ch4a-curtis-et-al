//
// Created by Curtis Barnhart on 2023-10-07.
//

#include "PureLexer.h"

namespace Lexing {
    PureLexer::PureLexer(const std::string &read_fname, const std::string &write_fname) : Lexer(read_fname) {
        this->writer.open(write_fname);
    }

    void PureLexer::gen_t_hook() {
        if (this->t_buffer->type == T_NULL) {
            this->writer.write("Next token is:         EOF | Next lexeme is EOF\n", 48);
            //this->writer.write(this->t_buffer->value.c_str(), (long) this->t_buffer->value.length());
            //this->writer.write("\n", 1);
            return;
        }
        static const char *types[] = {
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
        static const char *token_dec = "Next token is:";
        static const char *lexeme_dec = " | Next lexeme is ";

        this->writer.write(token_dec, 14);
        this->writer.write(types[this->t_buffer->type], 12);
        this->writer.write(lexeme_dec, 18);
        this->writer.write(this->t_buffer->value.c_str(), (long) this->t_buffer->value.length());
        this->writer.write("\n", 1);
    }
}
