#ifndef DOMAIN_ANALYZER_H
#define DOMAIN_ANALYZER_H

#include "./lexical_analyzer.h"
#include "./symbol.h"
#include "./token.h"
#include "./value.h"

Token *consumed_token;
Token *current_token;

int consumeToken(int type);

void predefineFunctions();

void analyzeDomain(Token*);

#endif