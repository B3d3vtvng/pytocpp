from src.nodes import *
from src.utils.built_in_funcs import BUILT_IN_FUNC_NAMES

class ASTOptimizationPass():
    def __init__(self, ast: AST, func_identifier_dict: dict[str: FuncDefNode]) -> None:
        self.ast = ast
        self.error = None
        self.func_identifier_dict = func_identifier_dict

    def optimize_ast(self) -> AST:
        self.remove_redundant_func_def()
        return self.ast
    
    def remove_redundant_func_def(self) -> None:
        for node in self.func_identifier_dict.values():
            if node.name in BUILT_IN_FUNC_NAMES: continue
            if not node.func_call_nodes:
                self.ast.traverse_node_by_id(node.id)
                func_def_node = self.ast.cur_node
                self.ast.detraverse_node()
                self.ast.cur_node.children.remove(func_def_node)
        return 0
            