#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <map>

namespace atom_c_compiler {
    enum Token_Code {
        // identifiers
        ID,
        // keywords
        IF,
        ELSE,
        WHILE,
        FOR,
        RETURN,
        BREAK,
        CONTINUE,
        // types
        VOID,
        INT,
        DOUBLE,
        CHAR,
        STRUCT,
        // constants
        CT_INT,
        CT_REAL,
        CT_CHAR,
        CT_STRING,
        // delimiters
        COMMA,
        COLON,
        SEMICOLON,
        LPAREN,
        RPAREN,
        LBRACKET,
        RBRACKET,
        LBRACE,
        RBRACE,
        // operators
        ASSIGN,
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        NOT,
        AND,
        OR,
        LT,
        GT,
        LE,
        GE,
        EQ,
        NE,
        DOT,
        // others
        SPACE,
        SLCOMMENT,
        MLCOMMENT,
        END,
    };

    class Token {
        public:
            Token_Code code;
            std::string value;
            // unsigned line;

            Token() = default;
            Token(Token_Code code);

            Token(Token_Code code, std::string value);
            // Token(Token_Code code, int value);
            // Token(Token_Code code, double value);

            ~Token() = default;

            void print();
            void error(const char *format, ...);

            // operator overloads
            Token& operator=(const Token&) = default;
    };
}

#endif