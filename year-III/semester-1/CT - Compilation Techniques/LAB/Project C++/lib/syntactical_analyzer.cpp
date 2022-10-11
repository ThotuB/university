#include "syntactical_analyzer.hpp"

#include <functional>
#include <iostream>
#include "token.hpp"

using namespace atom_c_compiler;

Syntactical_Analyzer::Syntactical_Analyzer(std::vector<Token> tokens)
    : tokens(tokens) {
}

bool Syntactical_Analyzer::consume(Token_Code code) {
    Token token = tokens[current_token_index];

    std::cout << code << " ?? " << token.code << "(" << token << ")" << std::endl;
    if (token.code == code) {
        current_token_index++;

        std::cout << "Consumed: " << token << " - " << current_token_index << std::endl;

        return true;
    }
    
    std::cout << "Expected: " << Token(code, 0) << std::endl;

    return false;
}

bool Syntactical_Analyzer::apply(std::function<bool(Syntactical_Analyzer)> rule) {
    // unsigned index = this->current_token_index;

    std::cout << this->current_token_index << std::endl;

    if (rule(*this)) {
        return true;
    }
    
    std::cout << this->current_token_index << std::endl;

    // this->current_token_index = index;

    return false;
}

bool ruleCode(Syntactical_Analyzer);
bool ruleStatementList(Syntactical_Analyzer);
bool ruleStatementElse(Syntactical_Analyzer);
bool ruleStatementIf(Syntactical_Analyzer);
bool ruleStatementWhile(Syntactical_Analyzer);
bool ruleStatementFor(Syntactical_Analyzer);
bool ruleStatementBreak(Syntactical_Analyzer);
bool ruleStatementReturn(Syntactical_Analyzer);
bool ruleStatementExpression(Syntactical_Analyzer);
bool ruleStatement(Syntactical_Analyzer);
bool ruleType(Syntactical_Analyzer);
bool ruleTypeName(Syntactical_Analyzer);
bool ruleArgumentList(Syntactical_Analyzer);
bool ruleExpression(Syntactical_Analyzer);
bool ruleExpressionAssign(Syntactical_Analyzer);
bool ruleExpressionOr(Syntactical_Analyzer);
bool ruleExpressionAnd(Syntactical_Analyzer);
bool ruleExpressionEquality(Syntactical_Analyzer);
bool ruleExpressionRelational(Syntactical_Analyzer);
bool ruleExpressionAddSub(Syntactical_Analyzer);
bool ruleExpressionMulDiv(Syntactical_Analyzer);
bool ruleExpressionCast(Syntactical_Analyzer);
bool ruleExpressionUnary(Syntactical_Analyzer);
bool ruleExpressionPostfix(Syntactical_Analyzer);
bool ruleExpressionPrimary(Syntactical_Analyzer);
bool ruleArray(Syntactical_Analyzer);
bool ruleDeclareVar(Syntactical_Analyzer);
bool ruleDeclareStruct(Syntactical_Analyzer);
bool ruleFuncParam(Syntactical_Analyzer);
bool ruleFuncParams(Syntactical_Analyzer);
bool ruleDeclareFunc(Syntactical_Analyzer);

bool ruleType(Syntactical_Analyzer analyzer) {
    if (analyzer.consume(INT)) return true;
    if (analyzer.consume(DOUBLE)) return true;
    if (analyzer.consume(CHAR)) return true;
    if (analyzer.consume(STRUCT)) return true;

    return false;
}

bool ruleTypeName(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleType)) return false;
    analyzer.apply(ruleArray);

    return true;
}

// initializer
bool ruleInit(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(ASSIGN)) return false;
    if (!analyzer.apply(ruleExpression)) return false;

    return true;
}

// argument list
bool ruleArgumentList(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpression)) return false;
    while (analyzer.consume(COMMA)) {
        if (!analyzer.apply(ruleExpression)) return false;
    }

    return true;
}

// array declaration
bool ruleArray(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(LBRACKET)) return false;
    analyzer.apply(ruleExpression);
    if (!analyzer.consume(RBRACKET)) return false;

    return true;
}

// expressions
bool ruleExpression(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionAssign)) return false;

    return true;
}

bool ruleExpressionAssign(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionOr)) return false;
    if (analyzer.consume(ASSIGN)) {
        if (!analyzer.apply(ruleExpressionAssign)) return false;
    }

    return true;
}

bool ruleExpressionOr(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionAnd)) return false;
    while (analyzer.consume(OR)) {
        if (!analyzer.apply(ruleExpressionAnd)) return false;
    }

    return true;
}

bool ruleExpressionAnd(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionEquality)) return false;
    while (analyzer.consume(AND)) {
        if (!analyzer.apply(ruleExpressionEquality)) return false;
    }

    return true;
}

bool ruleExpressionEquality(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionRelational)) return false;
    while (analyzer.consume(EQ) || analyzer.consume(NE)) {
        if (!analyzer.apply(ruleExpressionRelational)) return false;
    }

    return true;
}

bool ruleExpressionRelational(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionAddSub)) return false;
    while (analyzer.consume(LT) || analyzer.consume(LE) || analyzer.consume(GT) || analyzer.consume(GE)) {
        if (!analyzer.apply(ruleExpressionAddSub)) return false;
    }

    return true;
}

bool ruleExpressionAddSub(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionMulDiv)) return false;
    while (analyzer.consume(ADD) || analyzer.consume(SUB)) {
        if (!analyzer.apply(ruleExpressionMulDiv)) return false;
    }

    return true;
}

bool ruleExpressionMulDiv(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionCast)) return false;
    while (analyzer.consume(MUL) || analyzer.consume(DIV)) {
        if (!analyzer.apply(ruleExpressionCast)) return false;
    }

    return true;
}

bool ruleExpressionCast(Syntactical_Analyzer analyzer) {
    if (analyzer.consume(LPAREN)) {
        if (!analyzer.apply(ruleTypeName)) return false;
        if (!analyzer.consume(RPAREN)) return false;
        if (!analyzer.apply(ruleExpressionCast)) return false;

        return true;
    }
    if (!analyzer.apply(ruleExpressionUnary)) return false;

    return true;
}

bool ruleExpressionUnary(Syntactical_Analyzer analyzer) {
    if (analyzer.consume(ADD) || analyzer.consume(SUB)) {
        if (!analyzer.apply(ruleExpressionUnary)) return false;

        return true;
    }
    if (!analyzer.apply(ruleExpressionPostfix)) return false;

    return true;
}

bool ruleExpressionPostfix(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleExpressionPrimary)) return false;
    while (true) {
        if (analyzer.consume(LBRACKET)) {
            if (!analyzer.apply(ruleExpression)) return false;
            if (!analyzer.consume(RBRACKET)) return false;
        } else if (analyzer.consume(DOT)) {
            if (!analyzer.consume(ID)) return false;
        } else {
            break;
        }
    }

    return true;
}

bool ruleExpressionPrimary(Syntactical_Analyzer analyzer) {
    if (analyzer.consume(ID)) {
        if (analyzer.consume(LPAREN)) {
            analyzer.apply(ruleArgumentList);
            if (!analyzer.consume(RPAREN)) return false;

            return true;
        }
        return true;
    }
    if (analyzer.consume(CT_INT)) return true;
    if (analyzer.consume(CT_REAL)) return true;
    if (analyzer.consume(CT_CHAR)) return true;
    if (analyzer.consume(CT_STRING)) return true;
    if (analyzer.consume(LPAREN)) {
        if (!analyzer.apply(ruleExpression)) return false;
        if (!analyzer.consume(RPAREN)) return false;

        return true;
    }

    return false;
}

// statements
bool ruleStatementList(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(LBRACE)) return false;
    while (analyzer.apply(ruleDeclareVar) || analyzer.apply(ruleStatement));
    if (!analyzer.consume(RBRACE)) return false;

    return true;
}

bool ruleStatementElse(Syntactical_Analyzer analyzer) {
    if (analyzer.consume(ELSE)) {
        if (!analyzer.apply(ruleStatement)) return false;
    }

    return true;
}

bool ruleStatementIf(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(IF)) return false;
    if (!analyzer.consume(LPAREN)) return false;
    if (!analyzer.apply(ruleExpression)) return false;
    if (!analyzer.consume(RPAREN)) return false;
    if (!analyzer.apply(ruleStatement)) return false;
    analyzer.apply(ruleStatementElse);

    return true;
}

bool ruleStatementWhile(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(WHILE)) return false;
    if (!analyzer.consume(LPAREN)) return false;
    if (!analyzer.apply(ruleExpression)) return false;
    if (!analyzer.consume(RPAREN)) return false;
    if (!analyzer.apply(ruleStatement)) return false;

    return true;
}

bool ruleStatementFor(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(FOR)) return false;
    if (!analyzer.consume(LPAREN)) return false;
    analyzer.apply(ruleExpression);
    if (!analyzer.consume(SEMICOLON)) return false;
    analyzer.apply(ruleExpression);
    if (!analyzer.consume(SEMICOLON)) return false;
    analyzer.apply(ruleExpression);
    if (!analyzer.consume(RPAREN)) return false;
    if (!analyzer.apply(ruleStatement)) return false;

    return true;
}

bool ruleStatementBreak(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(BREAK)) return false;
    if (!analyzer.consume(SEMICOLON)) return false;

    return true;
}

bool ruleStatementReturn(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(RETURN)) return false;
    analyzer.apply(ruleExpression);
    if (!analyzer.consume(SEMICOLON)) return false;

    return true;
}

bool ruleStatementExpression(Syntactical_Analyzer analyzer) {
    analyzer.apply(ruleExpression);
    if (!analyzer.consume(SEMICOLON)) return false;

    return true;
}

bool ruleStatement(Syntactical_Analyzer analyzer) {
    if (analyzer.apply(ruleStatementList)) return true;
    if (analyzer.apply(ruleStatementIf)) return true;
    if (analyzer.apply(ruleStatementWhile)) return true;
    if (analyzer.apply(ruleStatementFor)) return true;
    if (analyzer.apply(ruleStatementBreak)) return true;
    if (analyzer.apply(ruleStatementReturn)) return true;
    if (analyzer.apply(ruleStatementExpression)) return true;

    return false;
}

// declaration
bool ruleDeclareVar(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleType)) return false;
    if (!analyzer.consume(ID)) return false;
    analyzer.apply(ruleArray);
    analyzer.apply(ruleInit);
    while (analyzer.consume(COMMA)) {
        if (!analyzer.consume(ID)) return false;
        analyzer.apply(ruleArray);
        analyzer.apply(ruleInit);
    }
    if (!analyzer.consume(SEMICOLON)) return false;

    return true;
}

bool ruleDeclareStruct(Syntactical_Analyzer analyzer) {
    if (!analyzer.consume(STRUCT)) return false;
    if (!analyzer.consume(ID)) return false;
    if (!analyzer.consume(LBRACE)) return false;
    std::cout << "lbrace" << std::endl;
    while (analyzer.apply(ruleDeclareVar)) {
    }
    std::cout << "ruledeclvar" << std::endl;
    if (!analyzer.consume(RBRACE)) return false;
    if (!analyzer.consume(SEMICOLON)) return false;

    return true;
}

bool ruleFuncParam(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleType)) return false;
    if (!analyzer.consume(ID)) return false;
    analyzer.apply(ruleArray);

    return true;
}

bool ruleFuncParams(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleFuncParam)) return false;
    while (analyzer.consume(COMMA)) {
        if (!analyzer.apply(ruleFuncParam)) return false;
    }

    return true;
}

bool ruleDeclareFunc(Syntactical_Analyzer analyzer) {
    if (!analyzer.apply(ruleType) && !analyzer.consume(VOID)) return false;
    if (!analyzer.consume(ID)) return false;
    if (!analyzer.consume(LPAREN)) {
        return false;    
    }
    analyzer.apply(ruleFuncParams);
    if (!analyzer.consume(RPAREN)) return false;
    if (!analyzer.apply(ruleStatementList)) return false;

    return true;
}

// code
bool ruleCode(Syntactical_Analyzer analyzer) {
    while (analyzer.apply(ruleDeclareStruct) || analyzer.apply(ruleDeclareFunc) || analyzer.apply(ruleDeclareVar)) {
    }
    if (!analyzer.consume(END)) return false;

    return true;
}

void Syntactical_Analyzer::analyze() {
    this->apply(ruleCode);
}