"""
Implements the built-in functions for the pytoc Python Transpiler

Creates a node for each function in the ast and specifies the expected type and the return type of the function
Stores the names of the built-in functions in a constant
Stores the node for each function in a constant for later use in parser.py
"""

from src.nodes import *

temp_ast = AST()
temp_ast.append_node(FuncDefNode("print", []))
temp_ast.cur_node.children[0].arg_types = [("int", "float", "bool", "str", "list")]
temp_ast.cur_node.children[0].return_type = ("none",)
temp_ast.append_node(FuncDefNode("input", ["msg"]))
temp_ast.cur_node.children[1].arg_types = [("str",)]
temp_ast.cur_node.children[1].return_type = ("str",)
temp_ast.append_node(FuncDefNode("len", ["var"]))
temp_ast.cur_node.children[2].arg_types = [("str", "list")]
temp_ast.cur_node.children[2].return_type = ("int",)
temp_ast.append_node(FuncDefNode("int", ["var"]))
temp_ast.cur_node.children[3].arg_types = [("str", "float")]
temp_ast.cur_node.children[3].return_type = ("int",)
temp_ast.append_node(FuncDefNode("str", ["var"]))
temp_ast.cur_node.children[4].arg_types = [("int", "float", "bool", "list", "str")]
temp_ast.cur_node.children[4].return_type = ("str",)
temp_ast.append_node(FuncDefNode("float", ["var"]))
temp_ast.cur_node.children[5].arg_types = [("str",)]
temp_ast.cur_node.children[5].return_type = ("float",)
temp_ast.append_node(FuncDefNode("range", ["start", "stop", "step"]))
temp_ast.cur_node.children[6].arg_types = [("int",), ("int",), ("int",)]
temp_ast.cur_node.children[6].return_type = ("list",)
temp_ast.append_node(FuncDefNode("strip", ["str", "strip"]))
temp_ast.cur_node.children[7].arg_types = [("str",), ("str",)]
temp_ast.cur_node.children[7].return_type = ("str",)
temp_ast.append_node(FuncDefNode("sqrt", ["num"]))
temp_ast.cur_node.children[8].arg_types = [("int",)]
temp_ast.cur_node.children[8].return_type = ("float",)
temp_ast.append_node(FuncDefNode("fread", ["fname"]))
temp_ast.cur_node.children[9].arg_types = [("str",)]
temp_ast.cur_node.children[9].return_type = ("str",)
temp_ast.append_node(FuncDefNode("freadlines", ["fname"]))
temp_ast.cur_node.children[9].arg_types = [("str",)]
temp_ast.cur_node.children[9].return_type = ("list",)
temp_ast.append_node(FuncDefNode("fcreate", ["fname"]))
temp_ast.cur_node.children[9].arg_types = [("str",)]
temp_ast.cur_node.children[9].return_type = ("none",)
temp_ast.append_node(FuncDefNode("fwrite", ["fname", "finput"]))
temp_ast.cur_node.children[10].arg_types = [("str",), ("str",)]
temp_ast.cur_node.children[10].return_type = ("none",)
temp_ast.append_node(FuncDefNode("fwritelines", ["fname", "finput"]))
temp_ast.cur_node.children[11].arg_types = [("str",), ("list",)]
temp_ast.cur_node.children[11].return_type = ("none",)
temp_ast.append_node(FuncDefNode("exit", ["exit_code"]))
temp_ast.cur_node.children[12].arg_types = [("int",)]
temp_ast.cur_node.children[12].return_type = ("none",)
temp_ast.append_node(FuncDefNode("list", ["str_input"]))
temp_ast.cur_node.children[13].arg_types = [("str",)]
temp_ast.cur_node.children[13].return_type = ("list",)
temp_ast.append_node(FuncDefNode("os_run", ["command"]))
temp_ast.cur_node.children[14].arg_types = [("str",)]
temp_ast.cur_node.children[14].return_type = ("int",)
temp_ast.append_node(FuncDefNode("sleep", ["duration"]))
temp_ast.cur_node.children[15].arg_types = [("int", "float")]
temp_ast.cur_node.children[15].return_type = ("none",)
temp_ast.append_node(FuncDefNode("time", []))
temp_ast.cur_node.children[16].arg_types = []
temp_ast.cur_node.children[16].return_type = ("float",)
temp_ast.append_node(FuncDefNode("time_str", []))
temp_ast.cur_node.children[17].arg_types = []
temp_ast.cur_node.children[17].return_type = ("str",)

BUILT_IN_FUNC_NAMES = [
    "print",
    "input", 
    "len", 
    "int", 
    "str", 
    "float", 
    "range",
    "strip",
    "sqrt",
    "fread",
    "freadlines",
    "fcreate",
    "fwrite",
    "fwritelines",
    "exit",
    "list",
    "os_run",
    "sleep",
    "time",
    "time_str"
]

BUILT_IN_FUNC_DICT = {}
for i in range(len(BUILT_IN_FUNC_NAMES)):
    BUILT_IN_FUNC_DICT[BUILT_IN_FUNC_NAMES[i]] = temp_ast.cur_node.children[i]

VAR_ARG_BUILT_IN_FUNCS = [
    "print",
    "input",
    "range",
    "strip",
    "exit"
]

PY_TO_CPP_BUILT_IN_FUNC_DICT = {
    "print": "RunTime::vprint",
    "input": "RunTime::vinput",
    "len": "RunTime::vlen",
    "int": "RunTime::toint",
    "str": "RunTime::tostr",
    "float": "RunTime::tofloat",
    "range": "RunTime::vrange",
    "strip": "RunTime::vstrip",
    "sqrt": "RunTime::vsqrt",
    "fread": "RunTime::fread",
    "freadlines": "RunTime::freadlines",
    "fcreate": "RunTime::fcreate",
    "fwrite": "RunTime::fwrite",
    "fwritelines": "RunTime::fwritelines",
    "exit": "RunTime::__exit",
    "list": "RunTime::vlist",
    "os_run": "RunTime::os_run",
    "sleep": "RunTime::sleep",
    "time": "RunTime::time",
    "time_str": "RunTime::time_str"
}
    