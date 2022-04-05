#ifndef LEXICAL_ANALYZER_HPP
#define LEXICAL_ANALYZER_HPP

#include "token.hpp"
#include <vector>

namespace atom_c_compiler {
    class Lexical_Analyzer {
        private:
            static Token get_next_token(std::string::iterator&);

        public:
            static std::vector<Token> tokenize(std::string);
    };
}

#endif