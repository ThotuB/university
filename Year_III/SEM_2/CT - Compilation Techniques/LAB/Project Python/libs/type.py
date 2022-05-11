from .symbol import *

class ValueCategory(Enum):
    R_VALUE = auto()
    L_VALUE = auto()


class Value:
    def __init__(self, type: Type, value: Optional[str | int | float]=None, category: ValueCategory=ValueCategory.R_VALUE):
        self.type = type
        self.value = value
        
        self.value_category = category
        
        
def cast_to_type(type_dest: Type, type_src: Type) :
    if type_src.size != -1:
        if type_dest.size != -1:
            if type_dest.type_base != type_src.type_base:
                raise Exception(f'Cannot cast array to array of different type')
        else:
            raise Exception(f'Cannot cast array type to non-array type')
    elif type_dest.size != -1:
        raise Exception(f'Cannot cast non-array type to array type')
    
    if type_src.type_base in [TypeBase.TB_CHAR, TypeBase.TB_INT, TypeBase.TB_REAL]:
        if type_dest.type_base in [TypeBase.TB_CHAR, TypeBase.TB_INT, TypeBase.TB_REAL]:
            return
    elif type_src.type_base == TypeBase.TB_STRUCT and type_dest.type_base == TypeBase.TB_STRUCT:
        if type_src.symbol != type_dest.symbol:
            raise Exception(f'Cannot cast struct to struct of different type')
        return
    raise Exception(f'Cannot cast {type_src} to {type_dest}')