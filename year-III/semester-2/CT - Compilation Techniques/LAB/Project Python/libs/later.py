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
        obj.value = term.value

    return True


def rule_expression_or(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_and, obj):
        return False
    while parser.consume(TokenCode.OR):
        term = Object()
        if not parser.apply(rule_expression_and, term):
            return False
        obj.value = obj.value or term.value

    return True


def rule_expression_and(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_equality, obj):
        return False
    while parser.consume(TokenCode.AND):
        term = Object()
        if not parser.apply(rule_expression_equality, term):
            return False
        obj.value = obj.value and term.value

    return True


def rule_expression_equality(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_relational, obj):
        return False
    while parser.consume(TokenCode.EQ) or parser.consume(TokenCode.NE):
        code = parser.consumed_tokens[-1].code
        term = Object()
        if not parser.apply(rule_expression_relational, term):
            return False
        match code:
            case TokenCode.EQ:
                obj.value = obj.value == term.value
            case TokenCode.NE:
                obj.value = obj.value != term.value

    return True


def rule_expression_relational(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_add_sub, obj):
        return False
    while parser.consume(TokenCode.LT) or parser.consume(TokenCode.LE) or parser.consume(TokenCode.GT) or parser.consume(TokenCode.GE):
        code = parser.consumed_tokens[-1].code
        term = Object()
        if not parser.apply(rule_expression_add_sub, term):
            return False
        match code:
            case TokenCode.LT:
                obj.value = obj.value < term.value
            case TokenCode.LE:
                obj.value = obj.value <= term.value
            case TokenCode.GT:
                obj.value = obj.value > term.value
            case TokenCode.GE:
                obj.value = obj.value >= term.value

    return True


def rule_expression_add_sub(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_mul_div, obj):
        return False
    while parser.consume(TokenCode.ADD) or parser.consume(TokenCode.SUB):
        code = parser.consumed_tokens[-1].code
        term = Object()
        if not parser.apply(rule_expression_mul_div, term):
            return False
        match code:
            case TokenCode.ADD:
                obj.value = obj.value + term.value
            case TokenCode.SUB:
                obj.value = obj.value - term.value

    return True


def rule_expression_mul_div(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_cast, obj):
        return False
    while parser.consume(TokenCode.MUL) or parser.consume(TokenCode.DIV):
        code = parser.consumed_tokens[-1].code
        term = Object()
        if not parser.apply(rule_expression_cast, term):
            return False
        match code:
            case TokenCode.MUL:
                obj.value = obj.value * term.value
            case TokenCode.DIV:
                obj.value = obj.value / term.value

    return True


def rule_expression_cast(parser: Parser, obj: Object) -> bool:
    if parser.consume(TokenCode.LPAREN):
        if not parser.apply(rule_type_name):
            return False
        if not parser.consume(TokenCode.RPAREN):
            return False
        if not parser.apply(rule_expression_cast):
            return False

        return True
    if not parser.apply(rule_expression_unary, obj):
        return False

    return True


def rule_expression_unary(parser: Parser, obj: Object) -> bool:
    if parser.consume(TokenCode.ADD) or parser.consume(TokenCode.SUB):
        code = parser.consumed_tokens[-1].code
        if not parser.apply(rule_expression_unary, obj):
            return False
        match code:
            case TokenCode.ADD:
                obj.value = +obj.value
            case TokenCode.SUB:
                obj.value = -obj.value

        return True
    if not parser.apply(rule_expression_postfix, obj):
        return False

    return True


def rule_expression_postfix(parser: Parser, obj: Object) -> bool:
    if not parser.apply(rule_expression_primary, obj):
        return False
    while True:
        if parser.consume(TokenCode.LBRACKET):
            term = Object(None)
            if not parser.apply(rule_expression, term):
                return False
            if not parser.consume(TokenCode.RBRACKET):
                return False
            obj.value = obj.value[term.value]
        elif parser.consume(TokenCode.DOT):
            if not parser.consume(TokenCode.ID):
                return False
            obj.value = obj.value[parser.consumed_tokens[-1].value]
        else:
            break

    return True


def rule_expression_primary(parser: Parser, obj: Object) -> bool:
    if parser.consume(TokenCode.ID):
        token = parser.consumed_tokens[-1]
        if parser.consume(TokenCode.LPAREN):
            parser.apply(rule_argument_list)
            if not parser.consume(TokenCode.RPAREN):
                return False

            return True
        else:
            obj.value = token.value
        return True
    if parser.consume(TokenCode.CT_INT):
        obj.value = parser.consumed_tokens[-1].value
        return True
    if parser.consume(TokenCode.CT_REAL):
        obj.value = parser.consumed_tokens[-1].value
        return True
    if parser.consume(TokenCode.CT_CHAR):
        obj.value = parser.consumed_tokens[-1].value
        return True
    if parser.consume(TokenCode.CT_STRING):
        obj.value = parser.consumed_tokens[-1].value
        return True
    if parser.consume(TokenCode.LPAREN):
        term = Object(None)
        if not parser.apply(rule_expression, term):
            return False
        if not parser.consume(TokenCode.RPAREN):
            return False
        obj.value = term.value

        return True

    return False