"""
Specifies the precedence of operators for different types of expressions
Also contains a map specifying which expression to check for in the Parser
"""

BINOP_OPERATOR_PRECEDENCE_DICT = {
    "TT_plus": 2,
    "TT_sub": 2,
    "TT_mul": 1,
    "TT_div": 1,
    "TT_mod": 1
}

CONDITION_OPERATOR_PRECEDENCE_DICT = {
    "TT_greater": 2,
    "TT_less": 2,
    "TT_gequ": 2,
    "TT_lequ": 2,
    "TT_dequ": 2,
    "TT_nequ": 2,
    "TT_and": 1,
    "TT_or": 1,
}

SLICE_OPERATOR_PRECEDENCE_DICT = {
    "TT_colon": 1
}

EXPR_MAP = {
    0: True, #simple_literal
    1: True, #array_literal
    2: True, #simple_var
    3: True, #array_var, includes str
    4: True, #slice_expr
    5: True, #func_call
    6: True, #un_op_expr
    7: True, #bin_op_expr
    8: True, #cond_expr
}

BINOP_FUNC_NAMES_DICT = {
    "+": "vadd",
    "-": "vsub",
    "*": "vmul",
    "/": "vdiv",
    "%": "vmod"
}

UNOP_FUNC_NAMES_DICT = {
    "not": "vnot",
    "-": "vneg"
}

LOGICAL_EXPR_FUNC_NAMES_DICT = {
    "and": "vand",
    "or": "vor",
    "<=": "LEQU",
    ">=": "GEQU",
    "<": "LESS",
    ">": "GREATER",
    "==": "vequ",
    "!=": "vnequ"
}

OPERATORS = [
    "TT_plus",
    "TT_sub",
    "TT_mul",
    "TT_div",
    "TT_mod",
    "TT_less",
    "TT_greater",
    "TT_equ",
    "TT_and",
    "TT_and",
    "TT_not"
]