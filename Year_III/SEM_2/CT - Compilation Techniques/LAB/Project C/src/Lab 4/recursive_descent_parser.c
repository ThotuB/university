#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/lexical_analyzer.h"
#include "../../lib/token.h"

token_t *consumed_token;
token_t *current_token;

int consumeToken(int type) {
    if (current_token->type == type) {
        consumed_token = current_token;
        current_token = current_token->next;

        printf("consumed token: %s\n", token_type_name[consumed_token->type]);

        return 1;
    }
    printf("* token: %s\n", token_type_name[type]);
    return 0;
}

/// RULES
// PROTOTYPES
int ruleCode();
int ruleStatementList();
int ruleStatementElse();
int ruleStatementIf();
int ruleStatementWhile();
int ruleStatementFor();
int ruleStatementBreak();
int ruleStatementReturn();
int ruleStatementExpression();
int ruleStatement();
int ruleType();
int ruleTypeName();
int ruleArgumentList();
int ruleExpression();
int ruleExpressionAssign();
int ruleExpressionOr();
int ruleExpressionAnd();
int ruleExpressionEquality();
int ruleExpressionRelational();
int ruleExpressionAddSub();
int ruleExpressionMulDiv();
int ruleExpressionCast();
int ruleExpressionUnary();
int ruleExpressionPostfix();
int ruleExpressionPrimary();
int ruleArray();
int ruleDeclareVar();
int ruleDeclareStruct();
int ruleFuncParam();
int ruleFuncParams();
int ruleDeclareFunc() ;

// variable types
int ruleType() {
    if (consumeToken(INT)) return 1;
    if (consumeToken(DOUBLE)) return 1;
    if (consumeToken(CHAR)) return 1;
    if (consumeToken(STRUCT)) return 1;

    return 0;
}

int ruleTypeName() {
    if (!ruleType()) return 0;
    ruleArray();

    return 1;
}

// argument list
int ruleArgumentList() {
    if (!ruleExpression()) return 0;
    while (consumeToken(COMMA)) {
        if (!ruleExpression()) return 0;
    }

    return 1;
}

// array declaration
int ruleArray() {
    if (!consumeToken(LBRACKET)) return 0;
    ruleExpression();
    if (!consumeToken(RBRACKET)) return 0;

    return 1;
}

// expressions
int ruleExpression() {
    if (!ruleExpressionAssign()) return 0;

    return 1;
}

int ruleExpressionAssign() {
    if (ruleExpressionUnary()) {
        if (!consumeToken(ASSIGN)) return 0;
        if (!ruleExpressionAssign()) return 0;

        return 1;
    }
    if (!ruleExpressionOr()) return 0;

    return 1;
}

int ruleExpressionOr() {
    if (ruleExpressionOr()) {
        if (!consumeToken(OR)) return 0;
        if (!ruleExpressionAnd()) return 0;

        return 1;
    }
    if (!ruleExpressionAnd()) return 0;

    return 1;
}

int ruleExpressionAnd() {
    if (ruleExpressionAnd()) {
        if (!consumeToken(AND)) return 0;
        if (!ruleExpressionEquality()) return 0;

        return 1;
    }
    if (!ruleExpressionEquality()) return 0;

    return 1;
}

int ruleExpressionEquality() {
    if (ruleExpressionEquality()) {
        if (!consumeToken(EQ) && !consumeToken(NE)) return 0;
        if (!ruleExpressionRelational()) return 0;

        return 1;
    }
    if (!ruleExpressionRelational()) return 0;

    return 1;
}

int ruleExpressionRelational() {
    if (ruleExpressionRelational()) {
        if (!consumeToken(LT) && !consumeToken(GT) && !consumeToken(LE) && !consumeToken(GE)) return 0;
        if (!ruleExpressionAddSub()) return 0;

        return 1;
    }
    if (!ruleExpressionAddSub()) return 0;

    return 1;
}

int ruleExpressionAddSub() {
    if (ruleExpressionAddSub()) {
        if (!consumeToken(ADD) && !consumeToken(SUB)) return 0;
        if (!ruleExpressionMulDiv()) return 0;

        return 1;
    }
    if (!ruleExpressionMulDiv()) return 0;

    return 1;
}

int ruleExpressionMulDiv() {
    if (ruleExpressionMulDiv()) {
        if (!consumeToken(MUL) && !consumeToken(DIV)) return 0;
        if (!ruleExpressionCast()) return 0;

        return 1;
    }
    if (!ruleExpressionCast()) return 0;

    return 1;
}

int ruleExpressionCast() {
    if (consumeToken(LPAREN)) {
        if (!ruleTypeName()) return 0;
        if (!consumeToken(RPAREN)) return 0;
        if (!ruleExpressionCast()) return 0;

        return 1;
    }
    if (!ruleExpressionUnary()) return 0;

    return 1;
}

int ruleExpressionUnary() {
    if (consumeToken(ADD) || consumeToken(SUB)) {
        if (!ruleExpressionUnary()) return 0;

        return 1;
    }
    if (!ruleExpressionPostfix()) return 0;

    return 1;
}

int ruleExpressionPostfix() {
    if (ruleExpressionPostfix()) {
        if (consumeToken(LBRACKET)) {
            if (!ruleExpression()) return 0;
            if (!consumeToken(RBRACKET)) return 0;

            return 1;
        }
        if (consumeToken(DOT)) {
            if (!consumeToken(ID)) return 0;

            return 1;
        }
    }
    if (!ruleExpressionPrimary()) return 0;

    return 1;
}

int ruleExpressionPrimary() {
    if (consumeToken(CT_INT)) return 1;
    if (consumeToken(CT_REAL)) return 1;
    if (consumeToken(CT_CHAR)) return 1;
    if (consumeToken(CT_STRING)) return 1;
    if (consumeToken(LPAREN)) {
        if (!ruleExpression()) return 0;
        if (!consumeToken(RPAREN)) return 0;

        return 1;
    }
    if (consumeToken(ID)) {
        if (consumeToken(LPAREN)) {
            ruleArgumentList();
            if (!consumeToken(RPAREN)) return 0;

            return 1;
        }
        return 1;
    }

    return 0;
}

// statements
int ruleStatementList() {
    if (!consumeToken(LBRACE)) return 0;
    while (ruleDeclareVar() || ruleStatement()) ;
    if (!consumeToken(RBRACE)) return 0;

    return 1;
}

int ruleStatementElse() {
    if (consumeToken(ELSE)) {
        if (!ruleStatement()) return 0;
    }

    return 1;
}

int ruleStatementIf() {
    if (!consumeToken(IF)) return 0;
    if (!consumeToken(LPAREN)) return 0;
    if (!ruleExpression()) return 0;
    if (!consumeToken(RPAREN)) return 0;
    if (!ruleStatement()) return 0;
    ruleStatementElse();

    return 1;
}

int ruleStatementWhile() {
    if (!consumeToken(WHILE)) return 0;
    if (!consumeToken(LPAREN)) return 0;
    if (!ruleExpression()) return 0;
    if (!consumeToken(RPAREN)) return 0;
    if (!ruleStatement()) return 0;

    return 1;
}

int ruleStatementFor() {
    if (!consumeToken(FOR)) return 0;
    if (!consumeToken(LPAREN)) return 0;
    ruleExpression();
    if (!consumeToken(SEMICOLON)) return 0;
    ruleExpression();
    if (!consumeToken(SEMICOLON)) return 0;
    ruleExpression();
    if (!consumeToken(RPAREN)) return 0;
    if (!ruleStatement()) return 0;

    return 1;
}

int ruleStatementBreak() {
    if (!consumeToken(BREAK)) return 0;
    if (!consumeToken(SEMICOLON)) return 0;

    return 1;
}

int ruleStatementReturn() {
    if (!consumeToken(RETURN)) return 0;
    ruleExpression();
    if (!consumeToken(SEMICOLON)) return 0;

    return 1;
}

int ruleStatementExpression() {
    ruleExpression();
    if (!consumeToken(SEMICOLON)) return 0;

    return 1;
}

int ruleStatement() {
    if (ruleStatementList()) return 1;
    if (ruleStatementIf()) return 1;
    if (ruleStatementWhile()) return 1;
    if (ruleStatementFor()) return 1;
    if (ruleStatementBreak()) return 1;
    if (ruleStatementReturn()) return 1;
    if (ruleStatementExpression()) return 1;

    return 0;
}

// declaration
int ruleDeclareVar() {
    if (!ruleType()) return 0;
    if (!consumeToken(ID)) return 0;
    ruleArray();
    while (consumeToken(COMMA)) {
        if (!consumeToken(ID)) return 0;
        ruleArray();
    }
    if (!consumeToken(SEMICOLON)) return 0;

    return 1;
}

int ruleDeclareStruct() {
    if (!consumeToken(STRUCT)) return 0;
    if (!consumeToken(ID)) return 0;
    if (!consumeToken(LBRACE)) return 0;
    while (ruleDeclareVar()) {
    }
    if (!consumeToken(RBRACE)) return 0;
    if (!consumeToken(SEMICOLON)) return 0;

    return 1;
}

int ruleFuncParam() {
    if (!ruleType()) return 0;
    if (!consumeToken(ID)) return 0;
    ruleArray();

    return 1;
}

int ruleFuncParams() {
    if (!ruleFuncParam()) return 0;
    while (consumeToken(COMMA)) {
        if (!ruleFuncParam()) return 0;
    }

    return 1;
}

int ruleDeclareFunc() {
    token_t *token = current_token;

    if (!ruleType() && !consumeToken(VOID)) return 0;
    if (!consumeToken(ID)) return 0;
    if (!consumeToken(LPAREN)) {
        current_token = token;
        return 0;    
    }
    ruleFuncParams();
    if (!consumeToken(RPAREN)) return 0;
    if (!ruleStatementList()) return 0;

    return 1;
}

// code
int ruleCode() {
    while (ruleDeclareStruct() || ruleDeclareFunc() || ruleDeclareVar()) {
    }
    if (!consumeToken(END)) return 0;

    return 1;
}

int main() {
    // read file into string
    FILE *fp = fopen("../../res/input.c", "r");

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *input = (char *)malloc(size + 1);
    fread(input, size, 1, fp);
    input[size] = '\0';

    printf("%s\n", input);

    tokenize(input);
    // showTokens();

    current_token = token_list;

    printf("%d", ruleCode());

    fclose(fp);

    return 0;
}