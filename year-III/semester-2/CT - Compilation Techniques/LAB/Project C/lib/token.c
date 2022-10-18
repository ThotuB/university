#include "token.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/// error handling
char *token_type_name[] = {
    // identifiers
    "ID",
    // keywords
    "IF",
    "ELSE",
    "WHILE",
    "FOR",
    "RETURN",
    "BREAK",
    "CONTINUE",
    // types
    "VOID",
    "INT",
    "DOUBLE",
    "CHAR",
    "STRUCT",
    // constants
    "CT_INT",
    "CT_REAL",
    "CT_CHAR",
    "CT_STRING",
    // delimiters
    "COMMA",
    "COLON",
    "SEMICOLON",
    "LPAREN",
    "RPAREN",
    "LBRACKET",
    "RBRACKET",
    "LBRACE",
    "RBRACE",
    // operators
    "ASSIGN",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "NOT",
    "AND",
    "OR",
    "LT",
    "GT",
    "LE",
    "GE",
    "EQ",
    "NE",
    "DOT",
    // others
    "SPACE",
    "SLCOMMENT",
    "MLCOMMENT",
    "END",
};

void error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(1);
}

void tokenError(Token *token, const char *format, ...) {
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, " at line %d\n", token->line);

    va_end(args);
    exit(1);
}

void printToken(Token* token) {
    printf("%s", token_type_name[token->type]);
        switch (token->type) {
            // identifier
            case ID:
                printf(" (%s)", token->str);
                break;

            // constants
            case CT_CHAR:
                printf(" (%c / %d)", token->integer, token->integer);
                break;

            case CT_STRING:
                printf(" (%s)", token->str);
                break;

            case CT_INT:
                printf(" (%d)", token->integer);
                break;

            case CT_REAL:
                printf(" (%f)", token->real);
                break;

            // others
            case SLCOMMENT:
                printf(" (%s)", token->str);
                break;

            case MLCOMMENT:
                printf(" (%s)", token->str);
                break;

            default:
                break;
        }
        printf("\n");
}