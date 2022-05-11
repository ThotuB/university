#include "token.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/// error handling

void error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
    exit(1);
}

void token_error(Token *token, const char *format, ...) {
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, " at line %d\n", token->line);

    va_end(args);
    exit(1);
}
