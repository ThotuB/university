#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <map>
#include <iostream>

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
            unsigned line;

            Token() = default;
            Token(Token_Code, unsigned);

            ~Token() = default;

            void error(const char *, ...);

            // operator overloads
            Token& operator=(const Token&) = default;
            friend std::ostream& operator<<(std::ostream&, const Token&);
    };

    class Valued_Token : public Token {
        public:
            std::string value;

            Valued_Token() = default;
            Valued_Token(Token_Code, unsigned, std::string);

            ~Valued_Token() = default;

            // operator overloads
            Valued_Token& operator=(const Valued_Token&) = default;
            friend std::ostream& operator<<(std::ostream&, const Valued_Token&);
    };
}

#endif