from src.nodes import *
from src.utils.built_in_funcs import BUILT_IN_FUNC_NAMES

class ASTOptimizationPass():
    def __init__(self, ast: AST, func_identifier_dict: dict[str: FuncDefNode]) -> None:
        self.ast = ast
        self.error = None
        self.func_identifier_dict = func_identifier_dict

    def optimize_ast(self) -> AST:
        self.remove_redundant_func_def()
        self.remove_redundant_children()
        return self.ast

    def remove_redundant_func_def(self) -> None:
        for node in self.func_identifier_dict.values():
            if node.name in BUILT_IN_FUNC_NAMES: continue
            if not node.func_call_nodes:
                self.ast.traverse_node_by_id(node.id)
                func_def_node = self.ast.cur_node
                self.ast.detraverse_node()
                self.ast.cur_node.children.remove(func_def_node)

        return None

    def remove_redundant_children(self, node: ASTNode = None) -> None:
        if not node:
            node = self.ast.base_node

        if "children" not in node.__dict__.keys():
            return
        
        children_nodes = [child_node.__class__.__name__ for child_node in node.children if child_node.__class__.__name__]

        if "BreakNode" in children_nodes:
            node.children = node.children[:children_nodes.index("BreakNode")+1]

        if "ContinueNode" in children_nodes:
            node.children = node.children[:children_nodes.index("ContinueNode")+1]

        if "ReturnNode" in children_nodes and node.children[children_nodes.index("ReturnNode")].parent.__class__.__name__ == "FuncDefNode":
            node.children = node.children[:children_nodes.index("ReturnNode")+1]


        for child_node in node.children:
            self.remove_redundant_children(child_node)

        return

        
            