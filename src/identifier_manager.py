from __future__ import annotations
from src.utils.header import INVALID_FUNC_NAMES, INVALID_VAR_NAMES
from src.nodes import ASTNode, FuncDefNode, AST
from src.utils.built_in_funcs import BUILT_IN_FUNC_DICT

class IdentifierManager():
    def __init__(self, ast: AST) -> None:
        self.global_identifier_container = IdentifierContainer()
        self.ast = ast

    def identifier_exists(self, identifier: str) -> bool:
        return self.get_cur_scope_identifier_container().identifier_exists(identifier)
    
    def get_identifier_node(self, identifier: str) -> ASTNode:
        return self.get_cur_scope_identifier_container().get_identifier_node(identifier)
    
    def set_identifier(self, identifier: str, value: ASTNode, force_global: bool = False) -> None:
        if force_global:
            return self.global_identifier_container.set_identifier(identifier, value)
        return self.get_cur_scope_identifier_container().set_identifier(identifier, value)

    def is_func_identifier(self, identifier: str):
        return self.get_cur_scope_identifier_container().is_func_identifier(identifier)
    
    def merge_identifiers(self, ident_man: IdentifierManager) -> None:
        self.global_identifier_container.merge_identifiers(ident_man.global_identifier_container)
        return None
    
    def get_func_identifier_dict(self):
        return self.get_cur_scope_identifier_container().get_func_identifier_dict()

    def get_cur_scope_identifier_container(self) -> IdentifierContainer:
        parent_node = self.ast.get_parent_node(FuncDefNode)
        if parent_node != -1:
            return parent_node.identifier_container
        return self.global_identifier_container

class IdentifierContainer():
    def __init__(self) -> None:
        self.identifier_dict = BUILT_IN_FUNC_DICT
        self.invalid_identifier_dict = {}
        self.func_identifiers = list(BUILT_IN_FUNC_DICT.keys())

    def identifier_exists(self, identifier: str) -> bool:
        identifier = self.check_invalid_identifier(identifier)
        return identifier in self.identifier_dict.keys()
    
    def get_identifier_node(self, identifier: str) -> ASTNode:
        identifier = self.check_invalid_identifier(identifier)
        if identifier not in self.identifier_dict.keys():
            raise NameError("Identifier non-existent in the current scope")
        return self.identifier_dict[identifier]
    
    def set_identifier(self, identifier: str, value: ASTNode) -> None:
        if identifier in INVALID_VAR_NAMES or identifier in INVALID_FUNC_NAMES:
            original_identifier = identifier
            identifier = "_" + identifier
            while identifier in self.identifier_dict:
                identifier = "_" + identifier
            self.invalid_identifier_dict[original_identifier] = identifier
        self.identifier_dict[identifier] = value
        if isinstance(value, FuncDefNode):
            self.func_identifiers.append(identifier)
        return None

    def is_func_identifier(self, identifier: str):
        identifier = self.check_invalid_identifier(identifier)
        return identifier in self.func_identifiers
    
    def merge_identifiers(self, ident_man: IdentifierManager) -> None:
        self.func_identifier_dict = list(set(self.func_identifiers + ident_man.func_identifiers))
        self.identifier_dict = ident_man.identifier_dict | self.identifier_dict
        self.invalid_identifier_dict = ident_man.invalid_identifier_dict | self.invalid_identifier_dict
        return None

    def check_invalid_identifier(self, identifier: str) -> str:
        if identifier in self.invalid_identifier_dict.keys():
            identifier = self.invalid_identifier_dict[identifier]

        return identifier
    
    def get_func_identifier_dict(self):
        func_identifier_dict = {key: value for key, value in self.identifier_dict.items() if isinstance(value, FuncDefNode)}
        return func_identifier_dict