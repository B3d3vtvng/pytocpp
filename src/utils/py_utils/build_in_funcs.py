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

BUILT_IN_FUNC_NAMES = [
    "print",
    "input", 
    "len", 
    "int", 
    "str", 
    "float", 
    "range"
]

BUILT_IN_FUNC_DICT = {}
for i in range(len(BUILT_IN_FUNC_NAMES)):
    BUILT_IN_FUNC_DICT[BUILT_IN_FUNC_NAMES[i]] = temp_ast.cur_node.children[i]
    