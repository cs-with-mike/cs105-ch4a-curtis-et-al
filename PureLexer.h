//
// Created by Curtis Barnhart on 2023-10-07.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_PURELEXER_H
#define CS_105_CH4A_CURTIS_ET_AL_PURELEXER_H

#include <string>
#include <fstream>

#include "Lexer.h"

namespace Lexing {
    class PureLexer final: public Lexer {
    public:
        PureLexer(const std::string &read_file_name, const std::string &write_file_name);
        ~PureLexer() override=default;

    private:
        std::ofstream writer;
        void token_hook() override;
    };
}

#endif //CS_105_CH4A_CURTIS_ET_AL_PURELEXER_H
