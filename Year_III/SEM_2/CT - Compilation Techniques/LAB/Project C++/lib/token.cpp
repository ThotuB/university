#include "token.hpp"
#include <cstdarg>

using namespace atom_c_compiler;

std::map<Token_Code, std::string> token_code_to_string = {
    {ID, "ID"},
    {IF, "IF"},
    {ELSE, "ELSE"},
    {WHILE, "WHILE"},
    {FOR, "FOR"},
    {RETURN, "RETURN"},
    {BREAK, "BREAK"},
    {CONTINUE, "CONTINUE"},
    {VOID, "VOID"},
    {INT, "INT"},
    {DOUBLE, "DOUBLE"},
    {CHAR, "CHAR"},
    {STRUCT, "STRUCT"},
    {CT_INT, "CT_INT"},
    {CT_REAL, "CT_REAL"},
    {CT_CHAR, "CT_CHAR"},
    {CT_STRING, "CT_STRING"},
    {COMMA, "COMMA"},
    {COLON, "COLON"},
    {SEMICOLON, "SEMICOLON"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {LBRACKET, "LBRACKET"},
    {RBRACKET, "RBRACKET"},
    {LBRACE, "LBRACE"},
    {RBRACE, "RBRACE"},
    {ASSIGN, "ASSIGN"},
    {ADD, "ADD"},
    {SUB, "SUB"},
    {MUL, "MUL"},
    {DIV, "DIV"},
    {MOD, "MOD"},
    {NOT, "NOT"},
    {AND, "AND"},
    {OR, "OR"},
    {LT, "LT"},
    {GT, "GT"},
    {LE, "LE"},
    {GE, "GE"},
    {EQ, "EQ"},
    {NE, "NE"},
    {DOT, "DOT"},
    {SPACE, "SPACE"},
    {SLCOMMENT, "SLCOMMENT"},
    {MLCOMMENT, "MLCOMMENT"},
    {END, "END"},
};

Token::Token(Token_Code code, unsigned line) {
    this->code = code;
    this->line = line;
}

Valued_Token::Valued_Token(Token_Code code, unsigned line, std::string value) {
    this->code = code;
    this->line = line;
    this->value = value;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Token: " << token_code_to_string[token.code];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Valued_Token& token) {
    os << "Token: " << token_code_to_string[token.code] << " " << token.value;
    return os;
}

void Token::error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}