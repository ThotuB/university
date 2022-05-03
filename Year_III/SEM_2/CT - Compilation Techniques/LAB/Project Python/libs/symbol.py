from enum import Enum, auto
from typing import List, Dict


class TypeBase(Enum):
    TB_INT = auto()
    TB_REAL = auto()
    TB_CHAR = auto()
    TB_STRUCT = auto()
    TB_VOID = auto()


class Class(Enum):
    CLASS_VAR = auto()
    CLASS_FUNC = auto()
    CLASS_EXTFUNC = auto()
    CLASS_STRUCT = auto()


class Memory(Enum):
    MEM_GLOBAL = auto()
    MEM_LOCAL = auto()
    MEM_ARG = auto()


class Symbol:
    def __init__(self, name: str, type: 'Type', cls: Class, memory: Memory, depth: int):
        self.name = name
        self.type = type
        self.cls = cls
        self.memory = memory
        self.depth = depth


class FuncSymbol(Symbol):
    def __init__(self, name: str, type: 'Type', cls: Class, memory: Memory, depth: int, args: List[Symbol]):
        super().__init__(name, type, cls, memory, depth)
        self.args = args


class StructSymbol(Symbol):
    def __init__(self, name: str, type: 'Type', cls: Class, memory: Memory, depth: int, members: List[Symbol]):
        super().__init__(name, type, cls, memory, depth)
        self.members = members


class Type:
    def __init__(self, type_base: TypeBase, symbol: Symbol, size: int):
        self.type_base = type_base
        self.symbol = symbol
        self.size = size

symbols = {}

def find_symbol(symbols: Dict[str, Symbol], name: str):
    return symbols.get(name)

def add_symbol(symbols: Dict[str, Symbol], symbol: Symbol):
    symbols[symbol.name] = symbol