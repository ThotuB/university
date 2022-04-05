#ifndef RECURSIVE_DESCENT_PARSER_HPP
#define RECURSIVE_DESCENT_PARSER_HPP

#include <vector>

#include "token.hpp"

namespace atom_c_compiler {
class Recursive_Descent_Parser {
    class Rule {
       protected:
        Recursive_Descent_Parser& parser;

       public:
        virtual bool apply();
    };

    class RuleCode : public Rule {
       public:
        bool apply();
    };

   private:
    Rule rule;
    std::vector<Token> tokens;
    int current_token_index;

    bool consume_token(Token_Code code);

   public:
    Recursive_Descent_Parser(std::vector<Token> tokens);
    void parse();
};
}  // namespace atom_c_compiler

#endif