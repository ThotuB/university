from typing import List, Tuple, Callable
from .token import *


class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.current = 0

    def consume(self, token_code: TokenCode) -> bool:
        if self.tokens[self.current].code == token_code:
            print(f'Consumed {self.tokens[self.current]}')
            self.current += 1
            return True
        # print(f'Expected {token_code.name}')
        return False

    def apply(self, rule: Callable[['Parser'], bool], *args) -> bool:
        current = self.current

        # print(f'Applying rule {rule.__name__}')
        if rule(self, *args):
            return True

        self.current = current
        return False


# variable types
def rule_type(parser: Parser) -> bool:
    if parser.consume(TokenCode.INT):
        return True
    if parser.consume(TokenCode.DOUBLE):
        return True
    if parser.consume(TokenCode.CHAR):
        return True
    if parser.consume(TokenCode.STRUCT):
        if not parser.consume(TokenCode.ID):
            return False
        return True

    return False


def rule_type_name(parser: Parser) -> bool:
    if not parser.apply(rule_type):
        return False
    parser.apply(rule_array)

    return True

# argument list
def rule_argument_list(parser: Parser) -> bool:
    if not parser.apply(rule_expression):
        return False
    while parser.consume(TokenCode.COMMA):
        if not parser.apply(rule_expression):
            return False

    return True

# array declaration
def rule_array(parser: Parser) -> bool:
    if not parser.consume(TokenCode.LBRACKET):
        return False
    parser.apply(rule_expression)
    if not parser.consume(TokenCode.RBRACKET):
        return False

    return True

# expressions
def rule_expression(parser: Parser) -> bool:
    if not parser.apply(rule_expression_assign):
        return False

    return True


def rule_expression_assign(parser: Parser) -> bool:
    if not parser.apply(rule_expression_or):
        return False
    if parser.consume(TokenCode.ASSIGN):
        if not parser.apply(rule_expression_assign):
            return False

    return True


def rule_expression_or(parser: Parser) -> bool:
    if not parser.apply(rule_expression_and):
        return False
    while parser.consume(TokenCode.OR):
        if not parser.apply(rule_expression_and):
            return False

    return True


def rule_expression_and(parser: Parser) -> bool:
    if not parser.apply(rule_expression_equality):
        return False
    while parser.consume(TokenCode.AND):
        if not parser.apply(rule_expression_equality):
            return False

    return True


def rule_expression_equality(parser: Parser) -> bool:
    if not parser.apply(rule_expression_relational):
        return False
    while parser.consume(TokenCode.EQ) or parser.consume(TokenCode.NE):
        if not parser.apply(rule_expression_relational):
            return False

    return True


def rule_expression_relational(parser: Parser) -> bool:
    if not parser.apply(rule_expression_add_sub):
        return False
    while parser.consume(TokenCode.LT) or parser.consume(TokenCode.LE) or parser.consume(TokenCode.GT) or parser.consume(TokenCode.GE):
        if not parser.apply(rule_expression_add_sub):
            return False

    return True


def rule_expression_add_sub(parser: Parser) -> bool:
    if not parser.apply(rule_expression_mul_div):
        return False
    while parser.consume(TokenCode.ADD) or parser.consume(TokenCode.SUB):
        if not parser.apply(rule_expression_mul_div):
            return False

    return True


def rule_expression_mul_div(parser: Parser) -> bool:
    if not parser.apply(rule_expression_cast):
        return False
    while parser.consume(TokenCode.MUL) or parser.consume(TokenCode.DIV):
        if not parser.apply(rule_expression_cast):
            return False

    return True


def rule_expression_cast(parser: Parser) -> bool:
    if parser.consume(TokenCode.LPAREN):
        if not parser.apply(rule_type_name):
            return False
        if not parser.consume(TokenCode.RPAREN):
            return False
        if not parser.apply(rule_expression_cast):
            return False

        return True
    if not parser.apply(rule_expression_unary):
        return False

    return True


def rule_expression_unary(parser: Parser) -> bool:
    if parser.consume(TokenCode.ADD) or parser.consume(TokenCode.SUB):
        if not parser.apply(rule_expression_unary):
            return False

        return True
    if not parser.apply(rule_expression_postfix):
        return False

    return True


def rule_expression_postfix(parser: Parser) -> bool:
    if not parser.apply(rule_expression_primary):
        return False
    while (1):
        if parser.consume(TokenCode.LBRACKET):
            if not parser.apply(rule_expression):
                return False
            if not parser.consume(TokenCode.RBRACKET):
                return False
        elif parser.consume(TokenCode.DOT):
            if not parser.consume(TokenCode.ID):
                return False
        else:
            break

    return True


def rule_expression_primary(parser: Parser) -> bool:
    if parser.consume(TokenCode.ID):
        if parser.consume(TokenCode.LPAREN):
            parser.apply(rule_argument_list)
            if not parser.consume(TokenCode.RPAREN):
                return False

            return True
        return True
    if parser.consume(TokenCode.CT_INT):
        return True
    if parser.consume(TokenCode.CT_REAL):
        return True
    if parser.consume(TokenCode.CT_CHAR):
        return True
    if parser.consume(TokenCode.CT_STRING):
        return True
    if parser.consume(TokenCode.LPAREN):
        if not parser.apply(rule_expression):
            return False
        if not parser.consume(TokenCode.RPAREN):
            return False

        return True

    return False

# statements
def rule_statement_list(parser: Parser) -> bool:
    if not parser.consume(TokenCode.LBRACE):
        return False
    while parser.apply(rule_declare_var) or parser.apply(rule_statement):
        pass
    if not parser.consume(TokenCode.RBRACE):
        return False

    return True


def rule_statement_else(parser: Parser) -> bool:
    if parser.consume(TokenCode.ELSE):
        if not parser.apply(rule_statement):
            return False

    return True


def rule_statement_if(parser: Parser) -> bool:
    if not parser.consume(TokenCode.IF):
        return False
    if not parser.consume(TokenCode.LPAREN):
        return False
    if not parser.apply(rule_expression):
        return False
    if not parser.consume(TokenCode.RPAREN):
        return False
    if not parser.apply(rule_statement):
        return False
    parser.apply(rule_statement_else)

    return True


def rule_statement_while(parser: Parser) -> bool:
    if not parser.consume(TokenCode.WHILE):
        return False
    if not parser.consume(TokenCode.LPAREN):
        return False
    if not parser.apply(rule_expression):
        return False
    if not parser.consume(TokenCode.RPAREN):
        return False
    if not parser.apply(rule_statement):
        return False

    return True


def rule_statement_for(parser: Parser) -> bool:
    if not parser.consume(TokenCode.FOR):
        return False
    if not parser.consume(TokenCode.LPAREN):
        return False
    parser.apply(rule_expression)
    if not parser.consume(TokenCode.SEMICOLON):
        return False
    parser.apply(rule_expression)
    if not parser.consume(TokenCode.SEMICOLON):
        return False
    parser.apply(rule_expression)
    if not parser.consume(TokenCode.RPAREN):
        return False
    if not parser.apply(rule_statement):
        return False

    return True


def rule_statement_break(parser: Parser) -> bool:
    if not parser.consume(TokenCode.BREAK):
        return False
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_statement_return(parser: Parser) -> bool:
    if not parser.consume(TokenCode.RETURN):
        return False
    parser.apply(rule_expression)
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_statement_expression(parser: Parser) -> bool:
    parser.apply(rule_expression)
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_statement(parser: Parser) -> bool:
    if parser.apply(rule_statement_list):
        return True
    if parser.apply(rule_statement_if):
        return True
    if parser.apply(rule_statement_while):
        return True
    if parser.apply(rule_statement_for):
        return True
    if parser.apply(rule_statement_break):
        return True
    if parser.apply(rule_statement_return):
        return True
    if parser.apply(rule_statement_expression):
        return True

    return False

# declaration
def rule_declare_var(parser: Parser) -> bool:
    if not parser.apply(rule_type):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    parser.apply(rule_array)
    while parser.consume(TokenCode.COMMA):
        if not parser.consume(TokenCode.ID):
            return False
        parser.apply(rule_array)
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_declare_struct(parser: Parser) -> bool:
    if not parser.consume(TokenCode.STRUCT):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    if not parser.consume(TokenCode.LBRACE):
        return False
    while parser.apply(rule_declare_var):
        pass
    if not parser.consume(TokenCode.RBRACE):
        return False
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_func_param(parser: Parser) -> bool:
    if not parser.apply(rule_type):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    parser.apply(rule_array)

    return True


def rule_func_params(parser: Parser) -> bool:
    if not parser.apply(rule_func_param):
        return False
    while parser.consume(TokenCode.COMMA):
        if not parser.apply(rule_func_param):
            return False

    return True


def rule_declare_func(parser: Parser) -> bool:
    if not parser.apply(rule_type) and not parser.consume(TokenCode.VOID):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    if not parser.consume(TokenCode.LPAREN):
        return False
    parser.apply(rule_func_params)
    if not parser.consume(TokenCode.RPAREN):
        return False
    if not parser.apply(rule_statement_list):
        return False

    return True

# code
def rule_code(parser: Parser) -> bool:
    while parser.apply(rule_declare_struct) or parser.apply(rule_declare_func) or parser.apply(rule_declare_var):
        pass
    if not parser.consume(TokenCode.END):
        return False

    return True


def analyze_syntactically(tokens: List[Token]):
    parser = Parser(tokens)
    parser.apply(rule_code)
