#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "token.h"

Token *token_list;
Token *tail_token;

char *current_char;
extern int line;

extern char *token_type_name[];

char *newString(char *start, char *end);

int between(char a, char x, char b);

int isKeyword(const char *str, const int str_len, const char *keyword, const int keyword_len);

int getNextToken();

void showTokens();

void tokenize(char *str);

#endif