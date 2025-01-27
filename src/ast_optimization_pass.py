from src.nodes import *
from src.utils.built_in_funcs import BUILT_IN_FUNC_NAMES

class ASTOptimizationPass():
    def __init__(self, ast: AST, identifier_manager) -> None:
        self.ast = ast
        self.error = None
        self.identifier_manager = identifier_manager

    def optimize_ast(self) -> AST:
        self.remove_redundant_func_def()
        self.remove_redundant_children()
        return self.ast

    def remove_redundant_func_def(self) -> None:
        for node in self.ast.base_node.children:
            if not isinstance(node, FuncDefNode):
                continue

            if node.func_call_nodes != None:
                continue

            self.ast.base_node.children.remove(node)
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

        
            