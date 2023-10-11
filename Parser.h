//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_PARSER_H
#define CS_105_CH4A_CURTIS_ET_AL_PARSER_H

#include <fstream> //import this to work with files
#include <sstream>
#include <string>
#include <memory>

#include "Lexer.h" //import the header file which comes with all the variables we'd need from the lexer.

namespace Parsing {
    class Parser {
    public:
        Parser(const std::string& read_fname, const std::string& write_fname);
        void parse();

    private:
        enum nonterminals {EXPRESSION, TERM, FACTOR};
        enum front_door {ENT, EXT};

        class ParserLexer : public Lexing::Lexer {
        public:
            ParserLexer();
            ParserLexer(const std::string &read_fname, std::ofstream *write_file, Parser *outer);
            ~ParserLexer() override=default;
            std::shared_ptr<Lexing::Token> next_token() override;
            std::shared_ptr<Lexing::Token> peek_token() override;
            ParserLexer &operator =(Parser::ParserLexer &&b) noexcept;

        private:
            void gen_t_hook() override;

            Parser *outer;
            std::ofstream *writer;
        };

        ParserLexer lexer;
        std::ofstream writer;
        int depth=0;

        void expression();
        void term();
        void factor ();
        void out_nonterminal(nonterminals nt, front_door fd);
        void out_error(const std::shared_ptr<Lexing::Token> &token);

        static std::string mapping[9];
        static std::string nonterminalmapping[3];
        char previous_char = '\0';
    };
}

#endif //CS_105_CH4A_CURTIS_ET_AL_PARSER_H
