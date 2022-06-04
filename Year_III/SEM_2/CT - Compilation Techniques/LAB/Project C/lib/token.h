#ifndef TOKEN_H
#define TOKEN_H

#define SAFE_ALLOC(var, type)                           \
    if ((var = (type *)malloc(sizeof(type))) == NULL) { \
        error("Out of memory");                         \
    }
    

extern char *token_type_name[];

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

void tokenError(Token *token, const char *format, ...);

void printToken(Token *token);

#endif
