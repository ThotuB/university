#include "domain_analyzer.h"

Token *consumed_token;
Token *current_token;

int consumeToken(int type) {
    if (current_token->type == type) {
        consumed_token = current_token;
        current_token = current_token->next;

        return 1;
    }
    return 0;
}

void addVar(Token *token, Type *t){
    Symbol *s;
    if (current_struct) {
        if(findSymbol(&current_struct->members, token->str))
            token_error(current_token, "symbol redefinition: %s", token->str);

        s = addSymbol(&current_struct->members, token->str, CLS_VAR);
        }
    else if (current_func){
        s = findSymbol(&symbols, token->str);
        if(s && s->depth == current_depth)
            token_error(current_token, "symbol redefinition: %s", token->str);

        s = addSymbol(&symbols, token->str, CLS_VAR);
        s->mem = MEM_LOCAL;
        }
    else{
        if(findSymbol(&symbols,token->str))
            token_error(current_token, "symbol redefinition: %s", token->str);

        s = addSymbol(&symbols, token->str, CLS_VAR);   
        s->mem = MEM_GLOBAL;
        }
    s->type = *t;
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
int ruleDeclareFunc();

// variable types
int ruleType(Type *type) {
    if (consumeToken(INT)) {
        type->typeBase = TB_INT;
        return 1;
    }
    if (consumeToken(DOUBLE)) {
        type->typeBase = TB_DOUBLE;
        return 1;
    }
    if (consumeToken(CHAR)) {
        type->typeBase = TB_CHAR;
        return 1;
    }
    if (consumeToken(STRUCT)) {
        if (!consumeToken(ID)) return 0;
        Token *token = consumed_token;

        Symbol *s = findSymbol(&symbols, token->str);
        if (s == NULL)
            token_error(current_token, "undefined symbol: %s", token->str);
        if(s->cls!=CLS_STRUCT)
            token_error(current_token, "%s is ! a struct", token->str);

        type->typeBase=TB_STRUCT;
        type->s=s;

        return 1;
    }

    return 0;
}

int ruleTypeName(Type *type) {
    if (!ruleType(type)) return 0;
    if (ruleArray(type)){

    }
    else {
        type->nElements = -1;
    }

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
int ruleArray(Type *type) {
    if (!consumeToken(LBRACKET)) return 0;
    ruleExpression();
    type->nElements = 0;
    if (!consumeToken(RBRACKET)) return 0;

    return 1;
}

// expressions
int ruleExpression() {
    if (!ruleExpressionAssign()) return 0;

    return 1;
}

int ruleExpressionAssign() {
    if (!ruleExpressionOr()) return 0;
    if (consumeToken(ASSIGN)) {
        if (!ruleExpressionAssign()) return 0;
    }

    return 1;
}

int ruleExpressionOr() {
    if (!ruleExpressionAnd()) return 0;
    while (consumeToken(OR)) {
        if (!ruleExpressionAnd()) return 0;
    }

    return 1;
}

int ruleExpressionAnd() {
    if (!ruleExpressionEquality()) return 0;
    while (consumeToken(AND)) {
        if (!ruleExpressionEquality()) return 0;
    }

    return 1;
}

int ruleExpressionEquality() {
    if (!ruleExpressionRelational()) return 0;
    while (consumeToken(EQ) || consumeToken(NE)) {
        if (!ruleExpressionRelational()) return 0;
    }

    return 1;
}

int ruleExpressionRelational() {
    if (!ruleExpressionAddSub()) return 0;
    while (consumeToken(LT) || consumeToken(LE) || consumeToken(GT) || consumeToken(GE)) {
        if (!ruleExpressionAddSub()) return 0;
    }

    return 1;
}

int ruleExpressionAddSub() {
    if (!ruleExpressionMulDiv()) return 0;
    while (consumeToken(ADD) || consumeToken(SUB)) {
        if (!ruleExpressionMulDiv()) return 0;
    }

    return 1;
}

int ruleExpressionMulDiv() {
    if (!ruleExpressionCast()) return 0;
    while (consumeToken(MUL) || consumeToken(DIV)) {
        if (!ruleExpressionCast()) return 0;
    }

    return 1;
}

int ruleExpressionCast() {
    if (consumeToken(LPAREN)) {
        Type *type = malloc(sizeof(Type));
        if (!ruleTypeName(type)) return 0;
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
    if (!ruleExpressionPrimary()) return 0;
    while (1) {
        if (consumeToken(LBRACKET)) {
            if (!ruleExpression()) return 0;
            if (!consumeToken(RBRACKET)) return 0;
        } else if (consumeToken(DOT)) {
            if (!consumeToken(ID)) return 0;
        } else {
            break;
        }
    }

    return 1;
}

int ruleExpressionPrimary() {
    if (consumeToken(ID)) {
        if (consumeToken(LPAREN)) {
            ruleArgumentList();
            if (!consumeToken(RPAREN)) return 0;

            return 1;
        }
        return 1;
    }
    if (consumeToken(CT_INT)) return 1;
    if (consumeToken(CT_REAL)) return 1;
    if (consumeToken(CT_CHAR)) return 1;
    if (consumeToken(CT_STRING)) return 1;
    if (consumeToken(LPAREN)) {
        if (!ruleExpression()) return 0;
        if (!consumeToken(RPAREN)) return 0;

        return 1;
    }

    return 0;
}

// statements
int ruleStatementList() {
    Symbol *start = symbols.end[-1];
    if (!consumeToken(LBRACE)) return 0;
    current_depth++;
    while (ruleDeclareVar() || ruleStatement());
    if (!consumeToken(RBRACE)) return 0;
    current_depth--;
    deleteSymbolsAfter(&symbols, start);

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
    Type *type = (Type *) malloc(sizeof(Type));
    if (!ruleType(type)) return 0;
    if (!consumeToken(ID)) return 0;
    Token *token = consumed_token;
    if (ruleArray(type)) {

    }
    else {
        type->nElements = -1;
    }
    addVar(token, type);
    while (consumeToken(COMMA)) {
        if (!consumeToken(ID)) return 0;
        if (ruleArray(type)) {

        }
        else {
            type->nElements = -1;
        }
        addVar(token, type);
    }
    if (!consumeToken(SEMICOLON)) return 0;

    return 1;
}

int ruleDeclareStruct() {
    if (!consumeToken(STRUCT)) return 0;
    if (!consumeToken(ID)) return 0;
    Token *token = consumed_token;
    if (!consumeToken(LBRACE)) return 0;
    if ( findSymbol(&symbols, token->str) )
        token_error(current_token, "symbol redefinition: %s", token->str);
    current_struct = addSymbol(&symbols, token->str,CLS_STRUCT);
    initSymbols(&current_struct->members);
    while (ruleDeclareVar()) {
    }
    if (!consumeToken(RBRACE)) return 0;
    if (!consumeToken(SEMICOLON)) return 0;
    current_struct = NULL;

    return 1;
}

int ruleFuncParam() {
    Type *type = (Type *) malloc(sizeof(Type));
    if (!ruleType(type)) return 0;
    if (!consumeToken(ID)) return 0;
    Token *token = consumed_token;
    if (ruleArray(type)) {

    }
    else {
        type->nElements = -1;
    }
    Symbol *s = addSymbol(&symbols, token->str, CLS_VAR);
    s->mem = MEM_ARG;
    s->type = *type;
    s = addSymbol(&current_func->args, token->str, CLS_VAR);
    s->mem = MEM_ARG;
    s->type = *type;

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
    Type* type = (Type*) malloc(sizeof(Type));
    if (!consumeToken(VOID)) {
        if (!ruleType(type)){
            return 0;
        }
        else {
            if ( consumeToken(MUL) ) {
                type->nElements = 0;
            }
            else {
                type->nElements = -1;
            }
        }
    }
    else {
        type->typeBase = TB_VOID;
    }
    if (!consumeToken(ID)) return 0;
    Token *token = consumed_token;
    if (!consumeToken(LPAREN)) {
        return 0;    
    }
    if ( findSymbol(&symbols, token->str) )
            tkerr(current_token, "symbol redefinition: %s", token->str);

    current_func = addSymbol(&symbols, token->str, CLS_FUNC);
    initSymbols(&current_func->args);
    current_func->type = type;
    current_depth++;
    ruleFuncParams();
    if (!consumeToken(RPAREN)) return 0;
    current_depth--;
    if (!ruleStatementList()) return 0;

    deleteSymbolsAfter(&symbols, current_func);
    current_func = NULL;

    return 1;
}

// code
int ruleCode() {
    while (ruleDeclareStruct() || ruleDeclareFunc() || ruleDeclareVar()) {
    }
    if (!consumeToken(END)) return 0;

    return 1;
}