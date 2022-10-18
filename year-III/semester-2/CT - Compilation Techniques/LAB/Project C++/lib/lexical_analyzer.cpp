#include "lexical_analyzer.hpp"
#include <iostream>

using namespace atom_c_compiler;

std::vector<Token> Lexical_Analyzer::tokenize(std::string str) {
    std::vector<Token> tokens;
    Token token;

    std::string::iterator it = str.begin();
    unsigned line = 1;

    do {
        token = Lexical_Analyzer::get_next_token(it, line);
        tokens.push_back(token);
    } while (token.code != END);

    return tokens;
}

Token Lexical_Analyzer::get_next_token(std::string::iterator& str_it, unsigned &line) {
    int state = 0;
    std::string::iterator it;;
    
    while (1) {
        char c = *str_it;

        switch (state) {
            case 0: {  // initial state
                // identifier / keyword / type
                if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_') {
                    state = 1;
                    it = str_it;
                }
                // constants
                else if (c == '\'') {
                    state = 13;
                    it = str_it;
                } else if (c == '\"') {
                    state = 16;
                    it = str_it;
                } else if (c == '0') {
                    state = 18;
                    it = str_it;
                } else if ('1' <= c && c <= '9') {
                    state = 21;
                    it = str_it;
                }
                // delimiters
                else if (c == ',') {
                    str_it++;
                    return Token(COMMA, line);
                } else if (c == ':') {
                    str_it++;
                    return Token(COLON, line);
                } else if (c == ';') {
                    str_it++;
                    return Token(SEMICOLON, line);
                } else if (c == '(') {
                    str_it++;
                    return Token(LPAREN, line);
                } else if (c == ')') {
                    str_it++;
                    return Token(RPAREN, line);
                } else if (c == '[') {
                    str_it++;
                    return Token(LBRACKET, line);
                } else if (c == ']') {
                    str_it++;
                    return Token(RBRACKET, line);
                } else if (c == '{') {
                    str_it++;
                    return Token(LBRACE, line);
                } else if (c == '}') {
                    str_it++;
                    return Token(RBRACE, line);
                }
                // operators
                else if (c == '=') {
                    state = 3;
                } else if (c == '+') {
                    str_it++;
                    return Token(ADD, line);
                } else if (c == '-') {
                    str_it++;
                    return Token(SUB, line);
                } else if (c == '*') {
                    str_it++;
                    return Token(MUL, line);
                } else if (c == '/') {
                    state = 4;
                } else if (c == '%') {
                    str_it++;
                    return Token(MOD, line);
                } else if (c == '!') {
                    state = 5;
                } else if (c == '&') {
                    state = 6;
                } else if (c == '|') {
                    state = 7;
                } else if (c == '<') {
                    state = 8;
                } else if (c == '>') {
                    state = 9;
                } else if (c == '.') {
                    str_it++;
                    return Token(DOT, line);
                }
                // others
                else if (c == ' ' || c == '\t') {
                    state = 0;
                } else if (c == '\n') {
                    line++;
                } else if (c == '\0') {
                    return Token(END, line);
                } else {
                    exit(1);
                }

                str_it++;
                break;
            }
            case 1: {  // state: [a-zA-Z_]
                if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_') {
                    state = 1;
                } else {
                    state = 2;
                    break;
                }

                str_it++;
                break;
            }
            case 2: {  // state: [a-zA-Z_] [a-zA-Z0-9_]*
                std::string str(it, str_it);

                // keywords
                if (!str.compare("if")) {
                    return Token(IF, line);
                } else if (!str.compare("else")) {
                    return Token(ELSE, line);
                } else if (!str.compare("while")) {
                    return Token(WHILE, line);
                } else if (!str.compare("for")) {
                    return Token(FOR, line);
                } else if (!str.compare("return")) {
                    return Token(RETURN, line);
                } else if (!str.compare("break")) {
                    return Token(BREAK, line);
                } else if (!str.compare("continue")) {
                    return Token(CONTINUE, line);
                }
                // types
                else if (!str.compare("void")) {
                    return Token(VOID, line);
                } else if (!str.compare("int")) {
                    return Token(INT, line);
                } else if (!str.compare("double")) {
                    return Token(DOUBLE, line);
                } else if (!str.compare("char")) {
                    return Token(CHAR, line);
                } else if (!str.compare("struct")) {
                    return Token(STRUCT, line);
                }
                // identifiers
                else {
                    return Valued_Token(ID, line, str);
                }
            }
            case 3: {  // state: =
                if (c == '=') {
                    str_it++;
                    return Token(EQ, line);
                } else {
                    return Token(ASSIGN, line);
                }
            }
            case 4: {  // state: /
                if (c == '/') {
                    state = 10;
                    it = str_it;
                } else if (c == '*') {
                    state = 11;
                } else {
                    return Token(DIV, line);
                }

                str_it++;
                break;
            }
            case 5: {  // state: !
                if (c == '=') {
                    str_it++;
                    return Token(NE, line);
                } else {
                    return Token(NOT, line);
                }
            }
            case 6: {  // state: &
                if (c == '&') {
                    str_it++;
                    return Token(AND, line);
                } else {
                    exit(1);
                }
            }
            case 7: {  // state: |
                if (c == '|') {
                    str_it++;
                    return Token(OR, line);
                } else {
                    exit(1);
                }
            }
            case 8: {  // state: <
                if (c == '=') {
                    str_it++;
                    return Token(LE, line);
                } else {
                    return Token(LT, line);
                }
            }
            case 9: {  // state: >
                if (c == '=') {
                    str_it++;
                    return Token(GE, line);
                } else {
                    return Token(GT, line);
                }
            }
            case 10: {  // state: //
                if (c == '\n' || c == '\r' || c == '\0') {
                    return Token(SLCOMMENT, line);
                } else {
                    state = 10;
                }

                str_it++;
                break;
            }
            case 11: {  // state: /*
                if (c == '*') {
                    state = 12;
                } else {
                    state = 11;
                }

                str_it++;
                break;
            }
            case 12: {  // state: /* ... *
                if (c == '/') {
                    str_it++;
                    return Token(MLCOMMENT, line);
                } else if (c == '*') {
                    state = 12;
                } else {
                    state = 11;
                }

                str_it++;
                break;
            }
            case 13: {  // state: [']
                if (c == '\\') {
                    state = 14;
                } else if (c == '\'') {
                    exit(1);
                } else {
                    state = 15;
                }

                str_it++;
                break;
            }
            case 14: {  // state: ['][\]
                if (c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\'' || c == '\"' || c == '?' || c == '0') {
                    state = 15;
                } else {
                    exit(1);
                }

                str_it++;
                break;
            }
            case 15: {  // state: [']( ESC | [^'\\] )
                if (c == '\'') {
                    str_it++;
                    return Valued_Token(CT_CHAR, line, std::string(it, str_it));
                } else {
                    exit(1);
                }
            }
            case 16: {  // state: ["]
                if (c == '\\') {
                    state = 17;
                } else if (c == '\"') {
                    str_it++;
                    return Valued_Token(CT_STRING, line, std::string(it, str_it));
                } else {
                    state = 16;
                }

                str_it++;
                break;
            }
            case 17: {  // state: ["][\]
                if (c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\"' || c == '?' || c == '0') {
                    state = 16;
                } else {
                    exit(1);
                }

                str_it++;
                break;
            }
            case 18: {  // state: 0
                if (c == 'x') {
                    state = 19;
                } else if (c == '.') {
                    state = 22;
                } else if ('0' <= c && c <= '7') {
                    state = 18;
                } else if (c == '8' || c == '9') {
                    state = 21;
                } else {
                    return Valued_Token(CT_INT, line, std::string(it, str_it));
                }

                str_it++;
                break;
            }
            case 19: {  // state: 0x
                if (('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) {
                    state = 20;
                } else {
                    exit(1);
                }

                str_it++;
                break;
            }
            case 20: {  // state: 0x[0-9a-fA-F]
                if (('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) {
                    state = 20;
                } else {
                    return Valued_Token(CT_INT, line, std::string(it, str_it));
                }

                str_it++;
                break;
            }
            case 21: {  // state: [1-9]
                if ('0' <= c && c <= '9') {
                    state = 21;
                } else if (c == '.') {
                    state = 22;
                } else {
                    return Valued_Token(CT_INT, line, std::string(it, str_it));
                }

                str_it++;
                break;
            }
            case 22: {  // state: [0-9]+.
                if ('0' <= c && c <= '9') {
                    state = 23;
                } else {
                    exit(1);
                }

                str_it++;
                break;
            }
            case 23: {  // state: [0-9]+.[0-9]+
                if (('0' <= c && c <= '9')) {
                    state = 23;
                } else {
                    return Valued_Token(CT_REAL, line, std::string(it, str_it));
                }

                str_it++;
                break;
            }
        }
    }

    return Token(END, line);
}

