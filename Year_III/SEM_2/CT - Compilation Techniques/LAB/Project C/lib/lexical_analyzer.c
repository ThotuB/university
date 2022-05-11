#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexical_analyzer.h"

int line = 0;

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

char *newString(char *start, char *end) {
    char *str = (char *)malloc(end - start + 1);
    strncpy(str, start, end - start);
    str[end - start] = '\0';
    return str;
}

int newInt(char *start, char *end) {
    char *str = (char *)malloc(end - start + 1);
    strncpy(str, start, end - start);
    str[end - start] = '\0';
    return atoi(str);
}

double newReal(char *start, char *end) {
    char *str = (char *)malloc(end - start + 1);
    strncpy(str, start, end - start);
    str[end - start] = '\0';
    return atof(str);
}

Token *addToken(token_type type) {
    Token *token;
    SAFE_ALLOC(token, Token);

    token->type = type;
    token->line = line;
    token->next = NULL;

    if (tail_token) {
        tail_token->next = token;
    } else {
        token_list = token;
    }
    tail_token = token;

    return token;
}

int between(char a, char x, char b) {
    return (a <= x && x <= b);
}

int isKeyword(const char *str, const int str_len, const char *keyword, const int keyword_len) {
    if (str_len != keyword_len) return 0;
    if (memcmp(str, keyword, str_len) != 0) return 0;
    return 1;
}

int getNextToken() {
    int state = 0;
    char c;
    char *str;
    int str_len = 0;
    Token *token;

    while (1) {
        c = *current_char;

        switch (state) {
            case 0: {  // initial state
                // identifier / keyword / type
                if (between('a', c, 'z') || between('A', c, 'Z') || c == '_') {
                    state = 1;
                    str = current_char;
                }
                // constants
                else if (c == '\'') {
                    state = 13;
                    str = current_char;
                } else if (c == '\"') {
                    state = 16;
                    str = current_char;
                } else if (c == '0') {
                    state = 18;
                    str = current_char;
                } else if (between('1', c, '9')) {
                    state = 21;
                    str = current_char;
                }
                // delimiters
                else if (c == ',') {
                    current_char++;
                    addToken(COMMA);
                    return COMMA;
                } else if (c == ':') {
                    current_char++;
                    addToken(COLON);
                    return COLON;
                } else if (c == ';') {
                    current_char++;
                    addToken(SEMICOLON);
                    return SEMICOLON;
                } else if (c == '(') {
                    current_char++;
                    addToken(LPAREN);
                    return LPAREN;
                } else if (c == ')') {
                    current_char++;
                    addToken(RPAREN);
                    return RPAREN;
                } else if (c == '[') {
                    current_char++;
                    addToken(LBRACKET);
                    return LBRACKET;
                } else if (c == ']') {
                    current_char++;
                    addToken(RBRACKET);
                    return RBRACKET;
                } else if (c == '{') {
                    current_char++;
                    addToken(LBRACE);
                    return LBRACE;
                } else if (c == '}') {
                    current_char++;
                    addToken(RBRACE);
                    return RBRACE;
                }
                // operators
                else if (c == '=') {
                    state = 3;
                } else if (c == '+') {
                    current_char++;
                    addToken(ADD);
                    return ADD;
                } else if (c == '-') {
                    current_char++;
                    addToken(SUB);
                    return SUB;
                } else if (c == '*') {
                    current_char++;
                    addToken(MUL);
                    return MUL;
                } else if (c == '/') {
                    state = 4;
                } else if (c == '%') {
                    current_char++;
                    addToken(MOD);
                    return MOD;
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
                    current_char++;
                    addToken(DOT);
                    return DOT;
                }
                // others
                else if (c == ' ' || c == '\t' || c == '\n') {
                    state = 0;
                } else if (c == '\0') {
                    addToken(END);
                    return END;
                } else {
                    token_error(addToken(END), "Unexpected character '%c'", c);
                }

                current_char++;
                break;
            }
            case 1: {  // state: [a-zA-Z_]
                if (between('a', c, 'z') || between('A', c, 'Z') || between('0', c, '9') || c == '_') {
                    state = 1;
                } else {
                    state = 2;
                    break;
                }

                current_char++;
                break;
            }
            case 2: {  // state: [a-zA-Z_] [a-zA-Z0-9_]*
                str_len = current_char - str;

                // keywords
                if (isKeyword(str, str_len, "if", 2)) {
                    addToken(IF);
                    return IF;
                } else if (isKeyword(str, str_len, "else", 4)) {
                    addToken(ELSE);
                    return ELSE;
                } else if (isKeyword(str, str_len, "while", 5)) {
                    addToken(WHILE);
                    return WHILE;
                } else if (isKeyword(str, str_len, "for", 3)) {
                    addToken(FOR);
                    return FOR;
                } else if (isKeyword(str, str_len, "return", 6)) {
                    addToken(RETURN);
                    return RETURN;
                } else if (isKeyword(str, str_len, "break", 3)) {
                    addToken(BREAK);
                    return BREAK;
                } else if (isKeyword(str, str_len, "continue", 8)) {
                    addToken(CONTINUE);
                    return CONTINUE;
                }
                // types
                else if (isKeyword(str, str_len, "void", 4)) {
                    addToken(VOID);
                    return VOID;
                }  else if (isKeyword(str, str_len, "int", 3)) {
                    addToken(INT);
                    return INT;
                } else if (isKeyword(str, str_len, "double", 6)) {
                    addToken(DOUBLE);
                    return DOUBLE;
                } else if (isKeyword(str, str_len, "char", 4)) {
                    addToken(CHAR);
                    return CHAR;
                } else if (isKeyword(str, str_len, "struct", 6)) {
                    addToken(STRUCT);
                    return STRUCT;
                }
                // identifiers
                else {
                    token = addToken(ID);
                    token->str = newString(str, current_char);
                    return ID;
                }
            }
            case 3: {  // state: =
                if (c == '=') {
                    current_char++;
                    addToken(EQ);
                    return EQ;
                } else {
                    addToken(ASSIGN);
                    return ASSIGN;
                }
            }
            case 4: {  // state: /
                if (c == '/') {
                    state = 10;
                    str = current_char;
                } else if (c == '*') {
                    state = 11;
                } else {
                    addToken(DIV);
                    return DIV;
                }

                current_char++;
                break;
            }
            case 5: {  // state: !
                if (c == '=') {
                    current_char++;
                    addToken(NE);
                    return NE;
                } else {
                    addToken(NOT);
                    return NOT;
                }
            }
            case 6: {  // state: &
                if (c == '&') {
                    current_char++;
                    addToken(AND);
                    return AND;
                } else {
                    token_error(addToken(END), "Invalid character");
                }
            }
            case 7: {  // state: |
                if (c == '|') {
                    current_char++;
                    addToken(OR);
                    return OR;
                } else {
                    token_error(addToken(END), "Invalid character");
                }
            }
            case 8: {  // state: <
                if (c == '=') {
                    current_char++;
                    addToken(LE);
                    return LE;
                } else {
                    addToken(LT);
                    return LT;
                }
            }
            case 9: {  // state: >
                if (c == '=') {
                    current_char++;
                    addToken(GE);
                    return GE;
                } else {
                    addToken(GT);
                    return GT;
                }
            }
            case 10: {  // state: //
                if (c == '\n' || c == '\r' || c == '\0') {
                    token = addToken(SLCOMMENT);
                    token->str = newString(str+1, current_char-1);
                    return SLCOMMENT;
                } else {
                    state = 10;
                }

                current_char++;
                break;
            }
            case 11: {  // state: /*
                if (c == '*') {
                    state = 12;
                } else {
                    state = 11;
                }

                current_char++;
                break;
            }
            case 12: {  // state: /* ... *
                if (c == '/') {
                    current_char++;
                    addToken(MLCOMMENT);
                    return MLCOMMENT;
                } else if (c == '*') {
                    state = 12;
                } else {
                    state = 11;
                }

                current_char++;
                break;
            }
            case 13: {  // state: [']
                if (c == '\\') {
                    state = 14;
                } else if (c == '\'') {
                    token_error(addToken(END), "Invalid character");
                } else {
                    state = 15;
                }

                current_char++;
                break;
            }
            case 14: {  // state: ['][\]
                if (c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\'' || c == '\"' || c == '?' || c == '0') {
                    state = 15;
                } else {
                    token_error(addToken(END), "Invalid character");
                }

                current_char++;
                break;
            }
            case 15: {  // state: [']( ESC | [^'\\] )
                if (c == '\'') {
                    current_char++;
                    token = addToken(CT_CHAR);
                    token->str = newString(str+1, current_char-1);
                    return CT_CHAR;
                } else {
                    token_error(addToken(END), "Invalid character");
                }
            }
            case 16: {  // state: ["]
                if (c == '\\') {
                    state = 17;
                } else if (c == '\"') {
                    current_char++;
                    token = addToken(CT_STRING);
                    token->str = newString(str+1, current_char-1);
                    return CT_STRING;
                } else {
                    state = 16;
                }

                current_char++;
                break;
            }
            case 17: {  // state: ["][\]
                if (c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '\\' || c == '\"' || c == '?' || c == '0') {
                    state = 16;
                } else {
                    token_error(addToken(END), "Invalid character");
                }

                current_char++;
                break;
            }
            case 18: {  // state: 0
                if (c == 'x') {
                    state = 19;
                } else if (c == '.') {
                    state = 22;
                } else if (between('0', c, '7')) {
                    state = 18;
                } else if (c == '8' || c == '9') {
                    state = 21;
                } else {
                    token = addToken(CT_INT);
                    token->integer = newInt(str, current_char);
                    return CT_INT;
                }

                current_char++;
                break;
            }
            case 19: {  // state: 0x
                if (between('0', c, '9') || between('a', c, 'f') || between('A', c, 'F')) {
                    state = 20;
                } else {
                    token_error(addToken(END), "Invalid character");
                }

                current_char++;
                break;
            }
            case 20: {  // state: 0x[0-9a-fA-F]
                if (between('0', c, '9') || between('a', c, 'f') || between('A', c, 'F')) {
                    state = 20;
                } else {
                    token = addToken(CT_INT);
                    token->integer = newInt(str, current_char);
                    return CT_INT;
                }

                current_char++;
                break;
            }
            case 21: {  // state: [1-9]
                if (between('0', c, '9')) {
                    state = 21;
                } else if (c == '.') {
                    state = 22;
                } else {
                    token = addToken(CT_INT);
                    token->integer = newInt(str, current_char);
                    return CT_INT;
                }

                current_char++;
                break;
            }
            case 22: {  // state: [0-9]+.
                if (between('0', c, '9')) {
                    state = 23;
                } else {
                    token_error(addToken(END), "Invalid character");
                }

                current_char++;
                break;
            }
            case 23: {  // state: [0-9]+.[0-9]+
                if (between('0', c, '9')) {
                    state = 23;
                } else {
                    token = addToken(CT_REAL);
                    token->real = newReal(str, current_char);
                    return CT_REAL;
                }

                current_char++;
                break;
            }
        }
    }

    return END;
}

void showTokens() {
    Token *current_token = token_list;
    for (; current_token->type != END; current_token = current_token->next) {
        printf("%s", token_type_name[current_token->type]);
        switch (current_token->type) {
            // identifier
            case ID:
                printf(" (%s)", current_token->str);
                break;

            // constants
            case CT_CHAR:
                printf(" (%c)", current_token->str[0]);
                break;

            case CT_STRING:
                printf(" (%s)", current_token->str);
                break;

            case CT_INT:
                printf(" (%d)", current_token->integer);
                break;

            case CT_REAL:
                printf(" (%f)", current_token->real);
                break;

            // others
            case SLCOMMENT:
                printf(" (%s)", current_token->str);
                break;

            case MLCOMMENT:
                printf(" (%s)", current_token->str);
                break;

            default:
                break;
        }
        printf("\n");
    }
}

void tokenize(char *str) {
    current_char = str;
    token_list = NULL;
    tail_token = NULL;

    int type = 0;
    do {
        type = getNextToken();
    } while (type != END);
}