from enum import Enum, auto


class TokenCode(Enum):
    # identifiers
    ID = auto()

    # keywords
    IF = auto()
    ELSE = auto()
    WHILE = auto()
    FOR = auto()
    RETURN = auto()
    BREAK = auto()
    CONTINUE = auto()

    # types
    VOID = auto()
    INT = auto()
    DOUBLE = auto()
    CHAR = auto()
    STRUCT = auto()

    # constants
    CT_INT = auto()
    CT_REAL = auto()
    CT_CHAR = auto()
    CT_STRING = auto()

    # delimiters
    COMMA = auto()
    COLON = auto()
    SEMICOLON = auto()
    LPAREN = auto()
    RPAREN = auto()
    LBRACKET = auto()
    RBRACKET = auto()
    LBRACE = auto()
    RBRACE = auto()

    # operators
    ASSIGN = auto()
    ADD = auto()
    SUB = auto()
    MUL = auto()
    DIV = auto()
    MOD = auto()
    NOT = auto()
    AND = auto()
    OR = auto()
    LT = auto()
    GT = auto()
    LE = auto()
    GE = auto()
    EQ = auto()
    NE = auto()
    DOT = auto()

    # others
    SPACE = auto()
    SLCOMMENT = auto()
    MLCOMMENT = auto()
    END = auto()


class Token:
    def __init__(self, code: TokenCode, line: int, column: int):
        self.code = code
        self.line = line
        self.column = column

    def __str__(self):
        return f'{self.line}:{self.column} - {self.code.name}'

    def error(self, msg: str) -> Exception:
        raise Exception(f'{self}: {msg}')


class ValuedToken(Token):
    def __init__(self, code: TokenCode, line: int, column: int, value: str | int | float):
        super().__init__(code, line, column)
        self.value = value

    def __str__(self):
        return f'{self.line}:{self.column} - {self.code.name} {self.value}'
