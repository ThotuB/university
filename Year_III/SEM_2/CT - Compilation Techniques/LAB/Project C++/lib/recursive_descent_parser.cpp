#include "recursive_descent_parser.hpp"

using namespace atom_c_compiler;

Recursive_Descent_Parser::Rule::Rule(Recursive_Descent_Parser& parser)
    : parser(parser) {}

Recursive_Descent_Parser::Recursive_Descent_Parser(std::vector<Token> tokens)
    : rule(*this), tokens(tokens), current_token_index(0) {
}

bool Recursive_Descent_Parser::consume_token(Token_Code code) {
    if (current_token_index >= tokens.size()) {
        throw "Unexpected end of file";
    }

    if (tokens[current_token_index].code != code) return false;

    current_token_index++;
    return true;
}

bool Recursive_Descent_Parser::RuleCode::apply() {
    if (parser.consume_token(INT)) return 1;
    if (parser.consume_token(DOUBLE)) return 1;
    if (parser.consume_token(CHAR)) return 1;
    if (parser.consume_token(STRUCT)) return 1;

    return 0;
}