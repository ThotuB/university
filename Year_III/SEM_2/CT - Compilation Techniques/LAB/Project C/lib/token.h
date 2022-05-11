#ifndef TOKEN_H
#define TOKEN_H

#define SAFE_ALLOC(var, type)                           \
    if ((var = (type *)malloc(sizeof(type))) == NULL) { \
        error("Out of memory");                         \
    }

typedef enum {
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
} token_type;

typedef struct _token_t {
    token_type type;
    union {
        char *str;
        int integer;
        double real;
    };
    int line;
    struct _token_t *next;
} Token;

void error(const char *format, ...);

void token_error(Token *token, const char *format, ...);

#endif
