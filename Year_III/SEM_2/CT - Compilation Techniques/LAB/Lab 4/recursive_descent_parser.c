#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Project/lib/token.h"
#include "../Project/lib/lexical_analyzer.h"

token_t *consumend_token;
token_t *current_token;

int consumeToken(int type) {
    if (current_token->type == type) {
        consumend_token = current_token;
        current_token = current_token->next;
        
        return 1;
    }
    return 0;
}

// rules
int ruleType() {
    token_t *token = current_token;

    if (consumeToken(INT)) return 1;
    if (consumeToken(FLOAT)) return 1;
    if (consumeToken(CHAR)) return 1;
    if (consumeToken(STR)) return 1;

    token_error(token, "Expected type");
}

int ruleStatement() {
    token_t *token = current_token;

    if (ruleExpression()) {
        if (!consumeToken(SEMICOLON)) token_error(token, "Expected ;");
        return 1;
    }
    if (ruleIf()) return 1;
    if (ruleWhile()) return 1;
    if (ruleReturn()) return 1;

    token_error(token, "Expected statement");
}

int ruleStatementBlock() {
    token_t *token = current_token;

    if (consumeToken(LBRACE)) {
        while (ruleStatement()) {
            if (consumeToken(RBRACE)) return 1;
        }
        token_error(token, "Expected }");
    }
    return 0;
}

int ruleElse() {
    token_t *token = current_token;

    if (consumeToken(ELSE)) {
        if (ruleStatementBlock()) return 1;
    }
    return 0;
}

int ruleIf() {
    token_t *token = current_token;

    if (!consumeToken(IF)) token_error(token, "Expected if");
    if (!consumeToken(LPAREN)) token_error(token, "Expected (");
    if (!ruleExpression()) token_error(token, "Invalid expression");
    if (!consumeToken(RPAREN)) token_error(token, "Expected )");
    if (!ruleStatementBlock()) token_error(token, "Invalid statement");
    if (ruleElse()) return 1;

    return 1;
}

int ruleWhile() {
    token_t *token = current_token;

    if (!consumeToken(WHILE)) return 0;
    if (!consumeToken(LPAREN)) token_error(token, "Expected (");
    if (!ruleExpression()) token_error(token, "Invalid expression");
    if (!consumeToken(RPAREN)) token_error(token, "Expected )");
    if (!ruleStatementBlock()) token_error(token, "Invalid statement");

    return 1;
}

int ruleReturn() {
    token_t *token = current_token;

    if (!consumeToken(RETURN)) return 0;
    ruleExpression();
    if (!consumeToken(SEMICOLON)) token_error(token, "Expected ;");

    return 1;
}

int ruleFunctionParam() {
    token_t *token = current_token;

    if (!consumeToken(ID)) return 0;
    if (!consumeToken(COLON)) token_error(token, "Expected :");
    if (!ruleType()) token_error(token, "Invalid type");

    return 1;
}

int ruleFunctionParamList() {
    token_t *token = current_token;

    if (!ruleFunctionParam()) return 0;
    if (consumeToken(COMMA)) {
        if (!ruleFunctionParamList()) token_error(token, "Invalid parameter list");
    }

    return 1;
}

int ruleFunction() {
    token_t *token = current_token;

    if (!consumeToken(FUNCTION)) return 0;
    if (!consumeToken(ID)) token_error(token, "Expected identifier");
    if (!consumeToken(LPAREN)) token_error(token, "Expected (");
    if (!ruleFunctionParamList()) token_error(token, "Invalid parameter list");
    if (!consumeToken(RPAREN)) token_error(token, "Expected )");
    if (!consumeToken(LBRACE)) token_error(token, "Expected {");
    if (!ruleStatementBlock()) token_error(token, "Invalid statement");
    if (!consumeToken(RBRACE)) token_error(token, "Expected }");

    return 1;
}

int main() {
    // read file into string
    FILE *fp = fopen("res/input.c", "r");

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *input = (char *)malloc(size + 1);
    fread(input, size, 1, fp);
    input[size] = '\0';

    printf("%s\n", input);

    tokenize(input);
    showTokens();

    fclose(fp);

    return 0;
}