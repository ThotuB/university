from typing import List, Tuple, Callable
from .token import *
from .symbol import *
from .type import *

class Object:
    def __init__(self, value: int | float | str | Type | StructType | Value=None):
        self.value = value
        
    def __str__(self) -> str:
        return f'Object - value: {self.value}'


class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.consumed_tokens: List[Token | ValuedToken] = []
        self.current = 0
        
        self.current_struct: Optional['StructSymbol'] = None
        self.current_func: Optional['FuncSymbol'] = None
        self.current_depth: int = 0
        self.symbols: List[Symbol] = []


    # Syntax Methods
    def consume(self, token_code: TokenCode) -> bool:
        if self.tokens[self.current].code == token_code:
            print(f'Consumed {self.tokens[self.current]}')
            
            self.consumed_tokens.append(self.tokens[self.current])
            self.current += 1

            return True
        return False


    def apply(self, rule: Callable[['Parser'], bool], *args) -> bool:
        current = self.current

        if rule(self, *args):
            return True

        self.current = current
        return False
    
    
    # Symbol Methods
    def find_symbol(self, name: str, symbols: List[Symbol]=None) -> Symbol | None:
        if symbols is None:
            symbols = self.symbols
        for symbol in reversed(symbols):
            if symbol.name == name:
                return symbol
        return None


    def add_symbol(self, symbol: Symbol, symbols: List[Symbol]=None):
        if symbols is None:
            symbols = self.symbols
        symbols.append(symbol)
        

    def add_variable(self, name: str, var_type: Type):
        if self.current_struct is not None:
            if self.find_symbol(name, self.current_struct.members) is not None:
                raise Exception(f'Variable {name} already defined')
            symbol = Symbol(name, var_type, Class.CLASS_VAR, Memory.MEM_LOCAL, self.current_depth)
            self.add_symbol(symbol, self.current_struct.members)
            
        elif self.current_func is not None:
            symbol = self.find_symbol(name)
            if symbol is not None and symbol.depth == self.current_depth:
                raise Exception(f'Variable {name} already defined')
            symbol = Symbol(name, var_type, Class.CLASS_VAR, Memory.MEM_LOCAL, self.current_depth)
            self.add_symbol(symbol)
            
        else:
            if self.find_symbol(name) is not None:
                raise Exception(f'Variable {name} already defined')
            symbol = Symbol(name, var_type, Class.CLASS_VAR, Memory.MEM_GLOBAL, self.current_depth)
            self.add_symbol(symbol)
            
            
    def delete_symbols_after(self, index: int):
        self.symbols = self.symbols[:index]


# variable types
def rule_type(parser: Parser, obj_type: Object) -> bool:
    if parser.consume(TokenCode.INT):
        obj_type.value = Type(TypeBase.TB_INT)
        return True
    if parser.consume(TokenCode.DOUBLE):
        obj_type.value = Type(TypeBase.TB_REAL)
        return True
    if parser.consume(TokenCode.CHAR):
        obj_type.value = Type(TypeBase.TB_CHAR)
        return True
    if parser.consume(TokenCode.STRUCT):
        if not parser.consume(TokenCode.ID):
            return False
        
        id = parser.consumed_tokens[-1].value
        symbol = parser.find_symbol(id)
        if not symbol:
            raise Exception(f'Undefined symbol {id}')
        if symbol.cls != Class.CLASS_STRUCT:
            raise Exception(f'{id} is not a struct')
        obj_type.value = StructType(symbol)
        
        return True

    return False


def rule_type_name(parser: Parser, obj_type: Object) -> bool:
    if not parser.apply(rule_type, obj_type):
        return False
    parser.apply(rule_array, obj_type)
        
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
def rule_array(parser: Parser, obj_type: Object) -> bool:
    if not parser.consume(TokenCode.LBRACKET):
        obj_type.value.size = -1
        return False
    obj = Object()
    if parser.apply(rule_expression, obj):
        if obj.value.value_category != ValueCategory.R_VALUE:
            raise Exception('Array size must be a constant')
        if obj.value.type_base != TypeBase.TB_INT:
            raise Exception('Array size must be an integer')
        obj_type.value.size = obj.value.value
    else:
        obj_type.value.size = 0
    if not parser.consume(TokenCode.RBRACKET):
        obj_type.value.size = -1
        return False

    return True

# expressions
def rule_expression(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_assign, obj):
        return False

    return True


def rule_expression_assign(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_or, obj):
        return False
    if parser.consume(TokenCode.ASSIGN):
        term = Object()
        if not parser.apply(rule_expression_assign, term):
            return False
        
        if obj.value.value_category != ValueCategory.L_VALUE:
            raise Exception('Cannot assign to a non-lvalue')
        if obj.value.size != -1 or term.value.size != -1:
            raise Exception('Cannot assign to an array')
        cast_to_type(obj.value, term.value)
        

    return True


def rule_expression_or(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_and, obj):
        return False
    while parser.consume(TokenCode.OR):
        term = Object()
        if not parser.apply(rule_expression_and, term):
            return False
        
        if obj.value.type.type_base == TypeBase.TB_STRUCT or term.value.type.type_base == TypeBase.TB_STRUCT:
            raise Exception('Cannot use struct in logical expression')
        obj.value.type 
    

    return True


def rule_expression_and(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_equality, obj):
        return False
    while parser.consume(TokenCode.AND):
        term = Object()
        if not parser.apply(rule_expression_equality, term):
            return False

    return True


def rule_expression_equality(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_relational, obj):
        return False
    while parser.consume(TokenCode.EQ) or parser.consume(TokenCode.NE):
        term = Object()
        if not parser.apply(rule_expression_relational, term):
            return False

    return True


def rule_expression_relational(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_add_sub, obj):
        return False
    while parser.consume(TokenCode.LT) or parser.consume(TokenCode.LE) or parser.consume(TokenCode.GT) or parser.consume(TokenCode.GE):
        term = Object()
        if not parser.apply(rule_expression_add_sub, term):
            return False

    return True


def rule_expression_add_sub(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_mul_div, obj):
        return False
    while parser.consume(TokenCode.ADD) or parser.consume(TokenCode.SUB):
        term = Object()
        if not parser.apply(rule_expression_mul_div, term):
            return False

    return True


def rule_expression_mul_div(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_cast, obj):
        return False
    while parser.consume(TokenCode.MUL) or parser.consume(TokenCode.DIV):
        term = Object()
        if not parser.apply(rule_expression_cast, term):
            return False

    return True


def rule_expression_cast(parser: Parser, obj: Object) -> bool:
    if parser.consume(TokenCode.LPAREN):
        if not parser.apply(rule_type_name):
            return False
        if not parser.consume(TokenCode.RPAREN):
            return False
        term = Object()
        if not parser.apply(rule_expression_cast, term):
            return False

        return True
    if not parser.apply(rule_expression_unary, obj):
        return False

    return True


def rule_expression_unary(parser: Parser, obj: Object) -> bool:
    if parser.consume(TokenCode.ADD) or parser.consume(TokenCode.SUB):
        term = Object()
        if not parser.apply(rule_expression_unary, term):
            return False

        return True
    if not parser.apply(rule_expression_postfix, obj):
        return False

    return True


def rule_expression_postfix(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_primary, obj):
        return False
    while (1):
        if parser.consume(TokenCode.LBRACKET):
            term = Object()
            if not parser.apply(rule_expression, term):
                return False
            if obj.value.type.size == -1:
                raise Exception('Cannot index a non-array')
            
            if not parser.consume(TokenCode.RBRACKET):
                return False
        elif parser.consume(TokenCode.DOT):
            if not parser.consume(TokenCode.ID):
                return False
            id = parser.consumed_tokens[-1].value
            symbol_struct: StructSymbol = obj.value.type.symbol
            symbol_field = parser.find_symbol(id, symbol_struct.members)
            if symbol_field is None:
                raise Exception('Field not found')
            obj.value = Value(symbol_field.type, None, ValueCategory.L_VALUE)
        else:
            break

    return True


def rule_expression_primary(parser: Parser, obj: Object) -> bool:
    if parser.consume(TokenCode.ID):
        id = parser.consumed_tokens[-1].value
        symbol = parser.find_symbol(id)
        if symbol is None:
            raise Exception(f'Undefined symbol {id}')
        obj.value = Value(symbol.type, None, ValueCategory.L_VALUE)
        
        if parser.consume(TokenCode.LPAREN):
            parser.apply(rule_argument_list)
            if not parser.consume(TokenCode.RPAREN):
                return False

            return True
        return True
    if parser.consume(TokenCode.CT_INT):
        token = parser.consumed_tokens[-1]
        obj.value = Value(Type(TypeBase.TB_INT, -1), ValueCategory.R_VALUE, token.value)
        return True
    if parser.consume(TokenCode.CT_REAL):
        token = parser.consumed_tokens[-1]
        obj.value = Value(Type(TypeBase.TB_REAL, -1), ValueCategory.R_VALUE, token.value)
        return True
    if parser.consume(TokenCode.CT_CHAR):
        token = parser.consumed_tokens[-1]
        obj.value = Value(Type(TypeBase.TB_CHAR, -1), ValueCategory.R_VALUE, token.value)
        return True
    if parser.consume(TokenCode.CT_STRING):
        token = parser.consumed_tokens[-1]
        obj.value = Value(Type(TypeBase.TB_CHAR, 0), ValueCategory.R_VALUE, token.value)
        return True
    if parser.consume(TokenCode.LPAREN):
        if not parser.apply(rule_expression, obj):
            return False
        if not parser.consume(TokenCode.RPAREN):
            return False

        return True

    return False

# statements
def rule_statement_list(parser: Parser) -> bool:
    index = len(parser.symbols)
    if not parser.consume(TokenCode.LBRACE):
        return False
    parser.current_depth += 1
    while parser.apply(rule_declare_var) or parser.apply(rule_statement):
        pass
    if not parser.consume(TokenCode.RBRACE):
        return False
    parser.current_depth -= 1
    parser.delete_symbols_after(index)

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
    obj = Object()
    if not parser.apply(rule_expression, obj):
        return False
    if obj.value.type_base == TypeBase.TB_STRUCT:
        raise Exception("Condition cannot be a struct")
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
    obj = Object()
    if not parser.apply(rule_expression, obj):
        return False
    if obj.value.type_base == TypeBase.TB_STRUCT:
        raise Exception("Condition cannot be a struct")
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
    obj_value_init = Object()
    parser.apply(rule_expression, obj_value_init)
        
    if not parser.consume(TokenCode.SEMICOLON):
        return False
    obj_value_cond = Object()
    if parser.apply(rule_expression, obj_value_cond):
        if obj_value_cond.value.type_base == TypeBase.TB_STRUCT:
            raise Exception("Condition cannot be a struct")
        
    if not parser.consume(TokenCode.SEMICOLON):
        return False
    obj_value_inc = Object()
    parser.apply(rule_expression, obj_value_inc)
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
    obj = Object()
    if parser.apply(rule_expression, obj):
        if parser.current_func.type.type_base == TypeBase.TB_VOID:
            raise Exception("Void function cannot return a value")
        cast_to_type(parser.current_func.type, obj.value)
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_statement_expression(parser: Parser) -> bool:
    obj = Object()
    parser.apply(rule_expression, obj)
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
    obj_type = Object()
    if not parser.apply(rule_type, obj_type):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    id = parser.consumed_tokens[-1].value
    parser.apply(rule_array, obj_type)
    parser.add_variable(id, obj_type.value)
    while parser.consume(TokenCode.COMMA):
        if not parser.consume(TokenCode.ID):
            return False
        id = parser.consumed_tokens[-1].value
        parser.apply(rule_array, obj_type)
        parser.add_variable(id, obj_type.value)
    if not parser.consume(TokenCode.SEMICOLON):
        return False

    return True


def rule_declare_struct(parser: Parser) -> bool:
    if not parser.consume(TokenCode.STRUCT):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    id = parser.consumed_tokens[-1].value
    if not parser.consume(TokenCode.LBRACE):
        return False
    
    if parser.find_symbol(id) is not None:
        raise Exception("struct already defined")
    parser.current_struct = StructSymbol(id, TypeBase.TB_STRUCT, Memory.MEM_GLOBAL, parser.current_depth)
    parser.add_symbol(parser.current_struct)
    
    while parser.apply(rule_declare_var):
        pass
    if not parser.consume(TokenCode.RBRACE):
        return False
    if not parser.consume(TokenCode.SEMICOLON):
        return False
    
    parser.current_struct = None

    return True


def rule_func_param(parser: Parser) -> bool:
    obj_type = Object()
    if not parser.apply(rule_type, obj_type):
        return False
    if not parser.consume(TokenCode.ID):
        return False
    id = parser.consumed_tokens[-1].value
    parser.apply(rule_array, obj_type)
    
    symbol = Symbol(id, obj_type.value, Class.CLASS_VAR, Memory.MEM_ARG, parser.current_depth)
    parser.add_symbol(symbol)
    parser.add_symbol(symbol, parser.current_func.args)

    return True


def rule_func_params(parser: Parser) -> bool:
    if not parser.apply(rule_func_param):
        return False
    while parser.consume(TokenCode.COMMA):
        if not parser.apply(rule_func_param):
            return False

    return True


def rule_declare_func(parser: Parser) -> bool:
    obj_type = Object()
    if not parser.consume(TokenCode.VOID):
        if not parser.apply(rule_type, obj_type):
            return False
        else:
            if parser.consume(TokenCode.MUL):
                obj_type.value.size = 0
            else:
                obj_type.value.size = -1
    else:
        obj_type.value = Type(TypeBase.TB_VOID)
        obj_type.value.size = -1
    if not parser.consume(TokenCode.ID):
        return False
    id = parser.consumed_tokens[-1].value
    if not parser.consume(TokenCode.LPAREN):
        return False
    if parser.find_symbol(id) is not None:
        raise Exception(f"Function {id} already defined")
    parser.current_func = FuncSymbol(id, obj_type.value, Memory.MEM_GLOBAL, parser.current_depth)
    parser.add_symbol(parser.current_func)
    index = len(parser.symbols)
    parser.current_depth += 1
    parser.apply(rule_func_params)
    if not parser.consume(TokenCode.RPAREN):
        return False
    parser.current_depth -= 1
    if not parser.apply(rule_statement_list):
        return False
    parser.delete_symbols_after(index)
    parser.current_func = None

    return True

# code
def rule_code(parser: Parser) -> bool:
    while parser.apply(rule_declare_struct) or parser.apply(rule_declare_func) or parser.apply(rule_declare_var):
        pass
    if not parser.consume(TokenCode.END):
        return False

    return True


def analyze_domain(tokens: List[Token]) -> List[Symbol]:
    parser = Parser(tokens)
    parser.apply(rule_code)
    
    return parser.symbols
