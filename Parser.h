//
// Created by Joshua Nielsen on 10/5/23.
//

#ifndef CS_105_CH4A_CURTIS_ET_AL_PARSER_H
#define CS_105_CH4A_CURTIS_ET_AL_PARSER_H

#include <fstream> //import this to work with files
#include <sstream>
#include <string>

#include "Lexer.h" //import the header file which comes with all the variables we'd need from the lexer.

class Parser {
    public:
        Parser(const std::string& read_file_name, const std::string& write_file_name);
        void parse();

    private:
        enum nonterminals {EXPRESSION, TERM, FACTOR};
        enum front_door {ENT, EXT};

        class ParserLexer : public Lexer {
        public:
            ParserLexer(); // TODO: complete
            ParserLexer(const std::string &read_file_name, std::ofstream *write_file, Parser *outer);
            ~ParserLexer() override=default;
            ParserLexer &operator =(Parser::ParserLexer &&b) noexcept;

        private:
            void token_hook() override;

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
        void out_token(const std::shared_ptr<Token> &token);
        void out_error(const std::shared_ptr<Token> &token);

        static std::string mapping[9];
        static std::string nonterminalmapping[3];
};



#endif //CS_105_CH4A_CURTIS_ET_AL_PARSER_H
