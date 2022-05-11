from enum import Enum, auto
from typing import List, Dict, Optional


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

    def __str__(self):
        return f'Symbol {self.name}: {self.type} {self.cls.name} {self.memory.name} ({self.depth})'


class FuncSymbol(Symbol):
    def __init__(self, name: str, type: 'Type', memory: Memory, depth: int):
        super().__init__(name, type, Class.CLASS_FUNC, memory, depth)
        self.args: List[Symbol] = []
        self.locals: List[Symbol] = []

    def __str__(self):
        return f'Function {self.name}: {self.type} {self.memory.name} ({self.depth})' + '\n'.join(map(str, self.args))


class StructSymbol(Symbol):
    def __init__(self, name: str, type: 'Type', memory: Memory, depth: int):
        super().__init__(name, type, Class.CLASS_STRUCT, memory, depth)
        self.members: List[Symbol] = []
        
    def __str__(self):
        return f'Struct {self.name}: {self.type} {self.memory.name} ({self.depth})'


class Type:
    def __init__(self, type_base: TypeBase, size: Optional[int]=None):
        self.type_base = type_base
        self.size = size
        
    def __str__(self):
        return f'{self.type_base.name} [{self.size}]'


class StructType(Type):
    def __init__(self, symbol: StructSymbol, size: Optional[int]=None):
        super().__init__(TypeBase.TB_STRUCT, size)
        self.symbol = symbol
        
    def __str__(self):
        return f'{self.type_base.name} {self.symbol.name}'