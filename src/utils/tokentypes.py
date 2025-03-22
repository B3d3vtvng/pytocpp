"""
Specifies the tokentypes and keyword tokentypes for the Lexer of the pytoc Python Transpiler
"""

TOKEN_TYPES = {
    "EOF": ("TT_eof", None), 
    "EOL": ("TT_eol", None),
    "PIND": ("TT_pind", None),
    "BOOL": ("TT_bool", None),
    "FLOAT": ("TT_FLOAT", None),
    "INT": ("TT_INT", None),
    "STR": ("TT_str", None),
    "NONE": ("TT_none", None),
    "IDENTIFIER": ("TT_identifier", None),
    "CMND": ("TT_cmnd", "#"), 
    "LPAREN": ("TT_lparen", "("),
    "RPAREN": ("TT_rparen", ")"),
    "LBRACKET": ("TT_lbracket", "["),
    "RBRACKET": ("TT_rbracket", "]"),
    "PLUS": ("TT_plus", "+"),
    "SUB": ("TT_sub", "-"),
    "MUL": ("TT_mul", "*"),
    "DIV": ("TT_div", "/"),
    "MOD": ("TT_mod", "%"),
    "EQU": ("TT_equ", "="),
    "EXCLAM": ("TT_exclam", "!"),
    "GREATER": ("TT_greater", ">"),
    "LESS": ("TT_less", "<"),
    "COMMA": ("TT_comma", ","),
    "COLON": ("TT_colon", ":"),
    "DOT": ("TT_dot", "."),
    "DQUOTE": ("TT_dquote", '"'),
    "SQUOTE": ("TT_squote", "'"),
    "DEF": ("TT_def", "def"),
    "RET": ("TT_ret", "return"),
    "IF": ("TT_if", "if"),
    "NOT": ("TT_not", "not"),
    "AND": ("TT_and", "and"),
    "OR": ("TT_or", "or"),
    "ELIF": ("TT_elif", "elif"),
    "ELSE": ("TT_else", "else"),
    "WHILE": ("TT_while", "while"),
    "FOR": ("TT_for", "for"), 
    "IN": ("TT_in", "in"),
    "IMPORT": ("TT_import", "import"),
    "CONTINUE": ("TT_continue", "continue"),
    "PASS": ("TT_pass", "pass"),
    "BREAK": ("TT_break", "break")
    }    

KEYWORDS = [
    "DEF",
    "EXTERN",
    "RETURN", 
    "IF", 
    "NOT", 
    "ELIF", 
    "ELSE", 
    "WHILE", 
    "FOR", 
    "IN",
    "AND",
    "OR"
]

TOKEN_ALIAS_TO_TOKEN_DICT = {
    "&&": "and",
    "||": "or"
}