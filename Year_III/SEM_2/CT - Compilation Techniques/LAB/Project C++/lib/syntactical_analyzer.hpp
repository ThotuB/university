#ifndef SYNTACTICAL_ANALYZER_HPP
#define SYNTACTICAL_ANALYZER_HPP

#include <functional>
#include <vector>

#include "token.hpp"

namespace atom_c_compiler {
class Syntactical_Analyzer {
   private:
    std::vector<Token> tokens;
    unsigned current_token_index = 0;

   public:
    Syntactical_Analyzer(std::vector<Token> tokens);
    bool consume(Token_Code code);
    bool apply(std::function<bool(Syntactical_Analyzer)> rule);

    void analyze();
};
}  // namespace atom_c_compiler

#endif