from typing import TextIO
from src.utils.built_in_funcs import BUILT_IN_FUNC_NAMES, PY_TO_CPP_BUILT_IN_FUNC_DICT
from src.utils.header import DEFAULT_HEADER, HEADER_MODULES, RUNTIME_INSERT_LINE, VALUE_INSERT_LINE, INCLUDE_INSERT_LINE, OPERATOR_TO_MODULE_DICT, BUILT_IN_FUNC_TO_MODULE_DICT, MAIN_WRAPPER, BUILT_IN_FUNC_TO_LIB_DICT, DEFAULT_GLOBS
from src.utils.operators import BINOP_FUNC_NAMES_DICT, UNOP_FUNC_NAMES_DICT, LOGICAL_EXPR_FUNC_NAMES_DICT
from src.nodes import *
from src.identifier_manager import IdentifierContainer

class CodeGenerator():
    def __init__(self, ast: AST, new_file_n: str, ident_container: IdentifierContainer, file_n: str) -> None:
        self.ast = ast
        self.new_file_name = new_file_n
        self.new_file = self.open_new_file(new_file_n)
        self.next_free_temp_idx = 0
        self.func_defs = []
        self.header = DEFAULT_HEADER
        self.header[7] = self.header[7].replace("%", f"\"{file_n}\"")
        self.module_dict = {element: False for element in HEADER_MODULES}
        self.pure_glob = False
        self.identifier_container = ident_container
        self.error = None

    def open_new_file(self, new_file_n: str) -> TextIO:
        """
        Purpose: Opens a file descriptor for the target file

        Takes the name of the target file

        Tries to open a new file with the given name
        Handles the case that the target file already exists by overwriting the existing file

        Returns file descriptor for the new file
        """
        try:
            new_file = open(new_file_n, "x")
        except FileExistsError:
            new_file = open(new_file_n, "w")
        
        return new_file

    def generate_code(self) -> None:
        output = MAIN_WRAPPER
        generated_output = ""
        globs = DEFAULT_GLOBS + self.make_globs()
        for i in range(len(self.ast.base_node.children)):
            self.ast.cur_node = self.ast.base_node.children[i]
            if self.ast.cur_node.__class__.__name__ != "FuncDefNode":
                generated_output += self.generate_node(target_string="%", indentation=4) + "\n"
            else:
                self.generate_node()
        output = output.replace("%", generated_output)
        if self.func_defs:
            output = '\n\n'.join(self.func_defs) + "\n\n" + output
        output = globs + "\n" + output
        self.resolve_header()
        output = self.header + "\n\n" + output
        self.new_file.write(output)
        self.new_file.close()
        return self.new_file_name
    
    def generate_node(self, target_string: str = "%", indentation: int = 0, **kw_args) -> str:
        """
        Generates code for the current node in the ast and inserts it into the string at the position specified by the % character

        Takes the target string to generate code for the current node and the current indentation\n
        Returns the given string with the generated code at the specified place
        """
        if self.ast.cur_node.__class__.__name__ == "ImportNode": return ""
        generator_func = self.get_generator_func()
        res = generator_func(target_string, indentation, **kw_args)
        return res
    
    def get_generator_func(self) -> callable: 
        cur_node_name = self.ast.cur_node.__class__.__name__
        cur_node_name = cur_node_name[:len(cur_node_name)-4]
        generator_func_name = ""
        for i, char in enumerate(cur_node_name):
            if char.upper() != char:
                generator_func_name += char
            else:
                generator_func_name += "_" + char.lower() if i != 0 else char.lower()

        if generator_func_name in ["string", "number", "bool", "none"]:
            generator_func_name = "simple_literal"
        elif generator_func_name == "array":
            generator_func_name += "_literal"
        elif generator_func_name in ["if", "elif", "else"]:
            generator_func_name = "conditional_statement"

        generator_func_name = "generate_" + generator_func_name
        generator_func = self.__getattribute__(generator_func_name)
        return generator_func
    
    def generate_assign(self, target_string: str, indentation: int) -> str:
        if self.ast.cur_node.left_expr.__class__.__name__ == "VarNode":
            type_annotator_str = "Value " if (self.pure_glob or not self.ast.get_parent_node(FuncDefNode) == -1) and self.ast.cur_node.first_define else ""
            output = f'{type_annotator_str}{self.ast.cur_node.name} = %;'
            self.ast.traverse_node("value")
            output = self.generate_node(output, in_expr = True)
            self.ast.detraverse_node()
        else:
            self.ast.traverse_node("value")
            value = self.generate_node(in_expr=True)
            self.ast.detraverse_node()
            self.ast.traverse_node("left_expr")
            self.ast.traverse_node("content")
            idx_expr = self.generate_idx_expr()
            self.ast.detraverse_node()
            self.ast.detraverse_node()
            self.include("vindex_assign")
            output = f"{self.ast.cur_node.name} = RunTime::vindex_assign({self.ast.cur_node.name}, {value}, std::vector<Value>{{{idx_expr}}}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\");"
        return " " * indentation + target_string.replace("%", output)
    
    def generate_func_call(self, target_string: str, indentation: int, in_expr: bool = False) -> str:
        args = []
        arg_count = len(self.ast.cur_node.args)
        if arg_count != 0:
            self.ast.traverse_node("args")
            for _ in range(arg_count):
                args.append(self.generate_node(in_expr = True))
                self.ast.next_child_node("args")
            self.ast.detraverse_node()
        name = self.ast.cur_node.name
        dbg_args = ""
        if name in BUILT_IN_FUNC_NAMES:
            if name in BUILT_IN_FUNC_TO_MODULE_DICT.keys():
                self.include(BUILT_IN_FUNC_TO_MODULE_DICT[name])
            name = PY_TO_CPP_BUILT_IN_FUNC_DICT[name]
            dbg_args = f"{self.ast.cur_node.line}, \"{self.get_function_scope()}\""
            if arg_count != 0: dbg_args = ", " + dbg_args
            if name == "RunTime::vprint" or name == "RunTime::vrange":
                return self.generate_var_arg_func_call(target_string, indentation, name, args, in_expr)
        if not in_expr:
            return target_string.replace("%", indentation * " " + name + "(" + ', '.join([arg for arg in args]) + dbg_args + ");")
        else:
            return target_string.replace("%", name + "(" + ', '.join([arg for arg in args]) + dbg_args + ")")
        
    def generate_var_arg_func_call(self, target_string: str, indentation: int, name: str, args: list[str], in_expr) -> str:
        dbg_args = f"{self.ast.cur_node.line}, \"{self.get_function_scope()}\", " if name == "RunTime::vrange" else ""
        if not in_expr:
            return target_string.replace("%", indentation * " " + name + "(" + dbg_args + ', '.join([arg for arg in args]) + ");")
        else:
            return target_string.replace("%", name + "(" + dbg_args + ', '.join([arg for arg in args]) + ")")
    
    def generate_simple_literal(self, target_string: str, indentation: int, **kw_args) -> str:
        node_class = self.ast.cur_node.__class__.__name__
        match node_class:
            case "NumberNode":
                return target_string.replace("%", f"Value({str(self.ast.cur_node.value)})")
            case "BoolNode":
                return target_string.replace("%", f"Value({"true" if self.ast.cur_node.value else "false"})")
            case "StringNode":
                return target_string.replace("%", f"Value({'"' + self.ast.cur_node.value + '"'})")
            case "NoneNode":
                return target_string.replace("%", "Value(std::monostate{})")
            case _:
                raise Exception("Invalid node!")
            
    def generate_array_literal(self, target_string: str, indentation: int, **kw_args) -> str:
        elements = []
        child_len = len(self.ast.cur_node.children)
        if child_len != 0:
            self.ast.traverse_node()
            for _ in range(child_len):
                elements.append(self.generate_node(in_expr=True))
                self.ast.next_child_node()
            self.ast.detraverse_node()
        return target_string.replace("%", "Value(std::vector<Value>{" + ''.join([element + ", " if elements.index(element) != len(elements)-1 else element for element in elements]) + "})")
    
    def generate_var(self, target_string: str, indentation: int, **kw_args) -> str:
        return target_string.replace("%", self.ast.cur_node.name)
    
    def generate_array_var(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("content")
        if self.ast.cur_node.__class__.__name__ == "SliceExpressionNode":
            self.include("vslice")
            if not self.ast.cur_node.right:
                binop_node = BinOpNode("-", self.ast.cur_node.parent.line)
                binop_node.right = NumberNode(1)
                lencall_node = FuncCallNode("len", self.ast.cur_node.parent.line)
                lencall_node.args = [VarNode(self.ast.cur_node.parent.name)]
                binop_node.left = lencall_node
                self.ast.append_node(binop_node, "right")
            if not self.ast.cur_node.left:
                self.ast.append_node(NumberNode(0), "left")

            self.ast.traverse_node("left")
            left = self.generate_node(in_expr=True)
            self.ast.detraverse_node()
            self.ast.traverse_node("right")
            right = self.generate_node(in_expr=True)
            self.ast.detraverse_node()
            self.ast.detraverse_node()

            return target_string.replace("%", f"RunTime::vslice({self.ast.cur_node.name}, {left}, {right}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")")
        
        self.include("vindex")
        idx_expr = self.generate_idx_expr()
        self.ast.detraverse_node()
        return target_string.replace("%", f"RunTime::vindex({self.ast.cur_node.name}, std::vector<Value>{{{idx_expr}}}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")")

    def generate_idx_expr(self) -> str:
        idx_expr = ""
        while True:
            idx_expr += self.generate_node(in_expr=True)
            if self.ast.next_child_node("content") == -1:
                break
            idx_expr += ", "

        return idx_expr
    
    def generate_bin_op(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("left")
        left = self.generate_node(in_expr = True)
        self.ast.detraverse_node()
        self.ast.traverse_node("right")
        right = self.generate_node(in_expr = True)
        self.ast.detraverse_node()

        self.include(OPERATOR_TO_MODULE_DICT[self.ast.cur_node.op])

        return target_string.replace("%", f"RunTime::{BINOP_FUNC_NAMES_DICT[self.ast.cur_node.op]}({left}, {right}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")")
    
    def generate_un_op(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("right")
        right = self.generate_node(in_expr = True)
        self.ast.detraverse_node()

        if self.ast.cur_node.op == "not":
            self.include("vnot")
        else:
            self.include("vneg")
        
        return target_string.replace("%", f"RunTime::{UNOP_FUNC_NAMES_DICT[self.ast.cur_node.op]}({right}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")")

    def generate_condition_expression(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("left")
        left = self.generate_node(in_expr = True)
        self.ast.detraverse_node()
        self.ast.traverse_node("right")
        right = self.generate_node(in_expr = True)
        self.ast.detraverse_node() 

        
        if self.ast.cur_node.op in ["and", "or", "!=", "=="]:
            output = f"RunTime::{LOGICAL_EXPR_FUNC_NAMES_DICT[self.ast.cur_node.op]}({left}, {right}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")"
        else:
            output = f"RunTime::vcompare({left}, {right}, {LOGICAL_EXPR_FUNC_NAMES_DICT[self.ast.cur_node.op]}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")"

        self.include(OPERATOR_TO_MODULE_DICT[self.ast.cur_node.op])
        return target_string.replace("%", output)
    
    def generate_conditional_statement(self, target_string: str, indentation: int, **kw_args) -> str:
        if self.ast.cur_node.__class__.__name__ != "ElseNode":
            self.ast.traverse_node("condition")
            condition = self.generate_node(f"RunTime::vcondition(%, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")", in_expr = True)
            self.include("vcondition")
            self.ast.detraverse_node()
        if self.ast.cur_node.__class__.__name__ == "IfNode":
            output = f"if ({condition}){{\n%}}"
        elif self.ast.cur_node.__class__.__name__ == "ElifNode":
            output = f"else if ({condition}){{\n%}}"
        else:
            output = f"else{{\n%}}"
        body = self.generate_body(indentation)
        output = indentation * " " + output.replace("%", body)
        output = output[:len(output)-1] + "\n" + indentation * " " + "}"
        return target_string.replace("%", output)
    
    def generate_while_loop(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("condition")
        condition = self.generate_node(f"RunTime::vcondition(%, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")", in_expr = True)
        self.include("vcondition")
        self.ast.detraverse_node()
        body = self.generate_body(indentation)
        output = f"{indentation * " "}while ({condition}){{\n{body}{indentation * " "}}}"
        return target_string.replace("%", output)

    def generate_body(self, indentation: int) -> list[str]:
        body = ""
        child_count = len(self.ast.cur_node.children)
        cur_node = self.ast.cur_node
        self.ast.traverse_node()
        for _ in range(child_count):
            if self.ast.cur_node.__class__.__name__ == "AssignNode" and self.ast.cur_node.value == None:
                self.ast.next_child_node()
                continue
            body += self.generate_node("%\n", indentation + 4)
            self.ast.next_child_node()
        self.ast.cur_node = cur_node
        return body
    
    def generate_for_loop(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("iter")
        iter = self.generate_node(in_expr = True)
        self.ast.detraverse_node()
        body = self.generate_body(indentation)
        output = indentation * " " + f"for (Value {self.ast.cur_node.iter_var_name} : RunTime::validate_iter({iter}, {self.ast.cur_node.line}, \"{self.get_function_scope()}\")){{\n{body}{indentation * " "}}}"
        self.include("validate_iter")
        return target_string.replace("%", output)
    
    def generate_func_def(self, target_string: str, indentation: int, **kw_args) -> None:
        body = self.generate_body(indentation)
        if len(self.ast.cur_node.arg_names) != 0:
            arg_prefix = "Value "
        else:
            arg_prefix = ""
        output = f"Value {self.ast.cur_node.name}({arg_prefix + ', Value '.join(self.ast.cur_node.arg_names)}){{\n{body}{indentation * " "}}}"
        self.func_defs.append(output)
        return None
    
    def generate_return(self, target_string: str, indentation: int, **kw_args) -> str:
        self.ast.traverse_node("return_value")
        return_value = self.generate_node(in_expr = True)
        self.ast.detraverse_node()
        output = indentation * " " + f"return {return_value};"
        return target_string.replace("%", output)
    
    def generate_continue(self, target_string: str, indentation: int, **kw_args) -> str:
        return indentation * " " + "continue;"
    
    def generate_pass(self, target_string: str, indentation: int, **kw_args) -> str:
        return indentation * " " + "// pass\n"
    
    def generate_break(self, target_string: str, indentation: int, **kw_args) -> str:
        return indentation * " " + "break;"
    
    def include(self, rt_func_name: str) -> None:
        if rt_func_name == "vnequ":
            self.include("vequ")
        if rt_func_name == "vequ":
            self.include("v_dequ")
        if rt_func_name in ["tostr", "vprint", "vinput"]:
            self.include("v_tostr")
        self.module_dict[rt_func_name] = True
        return None
    
    def resolve_header(self) -> None:
        included_libs = []
        include_insert_line = INCLUDE_INSERT_LINE
        value_insert_line = VALUE_INSERT_LINE
        runtime_insert_line = RUNTIME_INSERT_LINE
        included_modules = [module for module in self.module_dict.keys() if self.module_dict[module]]
        public_incl = False
        for included_module in included_modules:
            if included_module in BUILT_IN_FUNC_TO_LIB_DICT.keys() and BUILT_IN_FUNC_TO_LIB_DICT[included_module] not in included_libs:
                included_libs.append(BUILT_IN_FUNC_TO_LIB_DICT[included_module])
                added_lines = len(BUILT_IN_FUNC_TO_LIB_DICT[included_module])
                include_insert_line += added_lines
                value_insert_line += added_lines
                runtime_insert_line += added_lines
                self.include_lib(include_insert_line, included_module)
            target = "value" if included_module[:2] == "v_" else "runtime"
            cur_insert_line = value_insert_line if target == "value" else runtime_insert_line
            if target == "runtime" and not public_incl:
                self.header.insert(runtime_insert_line, "public:\n")
                runtime_insert_line += 1
                cur_insert_line += 1
                public_incl = True
            with open(f"lib/cpplib/{included_module}.cpp", "r") as module:
                content = module.readlines()
            inserted_line_count = 0
            for line in content:
                self.header.insert(cur_insert_line, line)
                cur_insert_line += 1
                inserted_line_count += 1
            self.header.insert(cur_insert_line, "\n")
            if target == "value":
                value_insert_line += inserted_line_count+1
            runtime_insert_line += inserted_line_count+1
        self.header = ''.join(self.header)
        return None
    
    def include_lib(self, insert_line: int, module: str) -> None:
        target_libs = BUILT_IN_FUNC_TO_LIB_DICT[module]
        for target_lib in target_libs:
            self.header.insert(insert_line, f"#include <{target_lib}>\n")
            insert_line += 1
        return None

    def make_globs(self) -> str:
        has_func = False
        for node in self.ast.base_node.children:
            if node.__class__ == FuncDefNode:
                has_func = True
                break

        if not has_func: 
            self.pure_glob = True
            return ""

        assign_nodes = [node for node in self.ast.base_node.children if node.__class__ == AssignNode]
        glob_str = ''.join([f"Value {node.name};\n" for node in assign_nodes])

        return glob_str
    
    def get_function_scope(self) -> str:
        function_scope = self.ast.get_parent_node(FuncDefNode)
        if function_scope == -1:
            return "__main__"
        
        function_scope = function_scope.name
        return self.identifier_container.get_invalid_identifier(function_scope)
        


    

            
