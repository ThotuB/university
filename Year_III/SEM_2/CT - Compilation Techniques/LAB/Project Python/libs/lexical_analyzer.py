from .token import *
from typing import List, Tuple


def analyze_lexically(text: str) -> List[Token]:
    line = 0
    column = -1

    def get_next_token(index: int) -> Tuple[Token, int]:
        nonlocal line, column
        state = 0

        value_index = 0
        while index < len(text):
            column += 1
            char = text[index]

            match state:
                case 0:  # initial state
                    # identifier / keyword / type
                    if 'a' <= char <= 'z' or 'A' <= char <= 'Z' or char == '_':
                        state = 1
                        value_index = index

                    # constants
                    elif char == '\'':
                        state = 13
                        value_index = index

                    elif char == '\"':
                        state = 16
                        value_index = index

                    elif char == '0':
                        state = 18
                        value_index = index

                    elif '1' <= char <= '9':
                        state = 21
                        value_index = index

                    # delimiters
                    elif char == ',':
                        return Token(TokenCode.COMMA, line, column), index + 1

                    elif char == ':':
                        return Token(TokenCode.COLON, line, column), index + 1

                    elif char == ';':
                        return Token(TokenCode.SEMICOLON, line, column), index + 1

                    elif char == '(':
                        return Token(TokenCode.LPAREN, line, column), index + 1

                    elif char == ')':
                        return Token(TokenCode.RPAREN, line, column), index + 1

                    elif char == '[':
                        return Token(TokenCode.LBRACKET, line, column), index + 1

                    elif char == ']':
                        return Token(TokenCode.RBRACKET, line, column), index + 1

                    elif char == '{':
                        return Token(TokenCode.LBRACE, line, column), index + 1

                    elif char == '}':
                        return Token(TokenCode.RBRACE, line, column), index + 1

                    # operators
                    elif char == '=':
                        state = 3

                    elif char == '+':
                        return Token(TokenCode.ADD, line, column), index + 1

                    elif char == '-':
                        return Token(TokenCode.SUB, line, column), index + 1

                    elif char == '*':
                        return Token(TokenCode.MUL, line, column), index + 1

                    elif char == '/':
                        state = 4

                    elif char == '%':
                        return Token(TokenCode.MOD, line, column), index + 1

                    elif char == '!':
                        state = 5

                    elif char == '&':
                        state = 6

                    elif char == '|':
                        state = 7

                    elif char == '<':
                        state = 8

                    elif char == '>':
                        state = 9

                    elif char == '.':
                        return Token(TokenCode.DOT, line, column), index + 1

                    # others
                    elif char == ' ' or char == '\t':
                        state = 0

                    elif char == '\n':
                        line += 1
                        column = -1

                    elif char == '\0':
                        return Token(TokenCode.END, line, column), None

                    else:
                        raise Exception("???")

                    index += 1

                case 1:  # state: [a-zA-Z_]
                    if 'a' <= char <= 'z' or 'A' <= char <= 'Z' or '0' <= char <= '9' or char == '_':
                        state = 1

                    else:
                        state = 2
                        continue

                    index += 1

                case 2:  # state: [a-zA-Z_] [a-zA-Z0-9_]*
                    value_str = text[value_index:index]

                    # keywords
                    if (value_str == "if"):
                        return Token(TokenCode.IF, line, column), index

                    elif (value_str == "else"):
                        return Token(TokenCode.ELSE, line, column), index

                    elif (value_str == "while"):
                        return Token(TokenCode.WHILE, line, column), index

                    elif (value_str == "for"):
                        return Token(TokenCode.FOR, line, column), index

                    elif (value_str == "return"):
                        return Token(TokenCode.RETURN, line, column), index

                    elif (value_str == "break"):
                        return Token(TokenCode.BREAK, line, column), index

                    elif (value_str == "continue"):
                        return Token(TokenCode.CONTINUE, line, column), index

                    # types
                    elif (value_str == "void"):
                        return Token(TokenCode.VOID, line, column), index

                    elif (value_str == "int"):
                        return Token(TokenCode.INT, line, column), index

                    elif (value_str == "double"):
                        return Token(TokenCode.DOUBLE, line, column), index

                    elif (value_str == "char"):
                        return Token(TokenCode.CHAR, line, column), index

                    elif (value_str == "struct"):
                        return Token(TokenCode.STRUCT, line, column), index

                    # identifiers
                    else:
                        return ValuedToken(TokenCode.ID, line, column, value_str), index

                case 3:  # state: =
                    if char == '=':
                        index += 1
                        return Token(TokenCode.EQ, line, column), index

                    else:
                        return Token(TokenCode.ASSIGN, line, column), index

                case 4:  # state: /
                    if char == '/':
                        state = 10
                        value_index = index

                    elif char == '*':
                        state = 11

                    else:
                        return Token(TokenCode.DIV, line, column), index

                    index += 1

                case 5:  # state: !
                    if char == '=':
                        return Token(TokenCode.NE, line, column), index + 1

                    else:
                        return Token(TokenCode.NOT, line, column), index

                case 6:  # state: &
                    if char == '&':
                        return Token(TokenCode.AND, line, column), index + 1

                    else:
                        exit(1)

                case 7:  # state: |
                    if char == '|':
                        return Token(TokenCode.OR, line, column), index + 1

                    else:
                        exit(1)

                case 8:  # state: <
                    if char == '=':
                        return Token(TokenCode.LE, line, column), index + 1

                    else:
                        return Token(TokenCode.LT, line, column), index

                case 9:  # state: >
                    if char == '=':
                        return Token(TokenCode.GE, line, column), index + 1

                    else:
                        return Token(TokenCode.GT, line, column), index

                case 10:  # state: #
                    if char == '\n' or char == '\r' or char == '\0':
                        return Token(TokenCode.SLCOMMENT, line, column), index

                    else:
                        state = 10

                    index += 1

                case 11:  # state: /*
                    if char == '*':
                        state = 12

                    else:
                        state = 11

                    index += 1

                case 12:  # state: /* ... *
                    if char == '/':
                        return Token(TokenCode.MLCOMMENT, line, column), index + 1

                    elif char == '*':
                        state = 12

                    else:
                        state = 11

                    index += 1

                case 13:  # state: [']
                    if char == '\\':
                        state = 14

                    elif char == '\'':
                        exit(1)

                    else:
                        state = 15

                    index += 1

                case 14:  # state: ['][\]
                    if char == 'a' or char == 'b' or char == 'f' or char == 'n' or char == 'r' or char == 't' or char == 'v' or char == '\\' or char == '\'' or char == '\"' or char == '?' or char == '0':
                        state = 15

                    else:
                        exit(1)

                    index += 1

                case 15:  # state: [']( ESC | [^'\\] )
                    if char == '\'':
                        return ValuedToken(TokenCode.CT_CHAR, line, column, text[value_index+1]), index + 1

                    else:
                        exit(1)

                case 16:  # state: ["]
                    if char == '\\':
                        state = 17

                    elif char == '\"':
                        return ValuedToken(TokenCode.CT_STRING, line, column, text[value_index+1:index]), index + 1

                    else:
                        state = 16

                    index += 1

                case 17:  # state: ["][\]
                    if char == 'a' or char == 'b' or char == 'f' or char == 'n' or char == 'r' or char == 't' or char == 'v' or char == '\\' or char == '\"' or char == '?' or char == '0':
                        state = 16

                    else:
                        exit(1)

                    index += 1

                case 18:  # state: 0
                    if char == 'x':
                        state = 19

                    elif char == '.':
                        state = 22

                    elif '0' <= char <= '7':
                        state = 18

                    elif char == '8' or char == '9':
                        state = 21
                        
                    elif char in ['e', 'E']:
                        state = 24

                    else:
                        return ValuedToken(TokenCode.CT_INT, line, column, int(text[value_index:index], 8)), index

                    index += 1

                case 19:  # state: 0x
                    if '0' <= char <= '9' or 'a' <= char <= 'f' or 'A' <= char <= 'F':
                        state = 20

                    else:
                        exit(1)

                    index += 1

                case 20:  # state: 0x[0-9a-fA-F]
                    if '0' <= char <= '9' or 'a' <= char <= 'f' or 'A' <= char <= 'F':
                        state = 20

                    else:
                        return ValuedToken(TokenCode.CT_INT, line, column, int(text[value_index:index], 16)), index

                    index += 1

                case 21:  # state: [1-9]
                    if '0' <= char and char <= '9':
                        state = 21

                    elif char == '.':
                        state = 22
                        
                    elif char in ['e', 'E']:
                        state = 24

                    else:
                        return ValuedToken(TokenCode.CT_INT, line, column, int(text[value_index:index])), index

                    index += 1

                case 22:  # state: [0-9]+.
                    if '0' <= char and char <= '9':
                        state = 23

                    else:
                        exit(1)

                    index += 1

                case 23:  # state: [0-9]+.[0-9]+
                    if '0' <= char <= '9':
                        state = 23
                        
                    elif char in ['e', 'E']:
                        state = 24

                    else:
                        return ValuedToken(TokenCode.CT_REAL, line, column, float(text[value_index:index])), index

                    index += 1
                    
                case 24:
                    if '0' <= char <= '9':
                        state = 26
                        
                    elif char in ['+', '-']:
                        state = 25
                        
                    else:
                        exit(1)
                        
                    index += 1
                    
                case 25:
                    if '0' <= char <= '9':
                        state = 26
                    
                    else:
                        exit(1)
                        
                    index += 1
                    
                case 26:
                    if '0' <= char <= '9':
                        state = 26
                    
                    else:
                        return ValuedToken(TokenCode.CT_REAL, line, column, float(text[value_index:index])), index

        return Token(TokenCode.END, line, column), None

    index = 0
    tokens = []
    while index is not None:
        token, index = get_next_token(index)
        if token.code in [TokenCode.SLCOMMENT, TokenCode.MLCOMMENT]:
            continue
        tokens.append(token)

    return tokens
