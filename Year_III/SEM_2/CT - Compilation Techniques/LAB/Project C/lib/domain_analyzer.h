#ifndef DOMAIN_ANALYZER_H
#define DOMAIN_ANALYZER_H

#include "./lexical_analyzer.h"
#include "./symbol.h"
#include "./token.h"

Token *consumed_token;
Token *current_token;

int consumeToken(int type);

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

#endif