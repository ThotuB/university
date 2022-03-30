#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "token.h"

#define SAFE_ALLOC(var, type)                           \
    if ((var = (type *)malloc(sizeof(type))) == NULL) { \
        error("Out of memory");                         \
    }

token_t *token_list;
token_t *tail_token;

char *current_char;
extern int line;

extern char *token_type_name[];

char *newString(char *start, char *end);

int between(char a, char x, char b);

int is_keyword(const char *str, const int str_len, const char *keyword, const int keyword_len);

int getNextToken();

void showTokens();

void tokenize(char *str);

#endif