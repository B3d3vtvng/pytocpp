from __future__ import annotations
from src.utils.header import INVALID_IDENTIFIERS
from src.nodes import ASTNode, FuncDefNode, AST
from src.utils.built_in_funcs import BUILT_IN_FUNC_DICT
from copy import deepcopy

class IdentifierManager():
    def __init__(self, ast: AST) -> None:
        self.global_identifier_container = IdentifierContainer()
        self.ast = ast

    def get_relative_identifier(self, identifier: str) -> str:
        return self.get_cur_scope_identifier_container().check_invalid_identifier(identifier)

    def get_invalid_identifier(self, name: str) -> str:
        return self.global_identifier_container.get_invalid_identifier(name)

    def generate_relative_identifier(self, name: str):
        return self.get_cur_scope_identifier_container().generate_relative_identifier(name)

    def identifier_exists(self, identifier: str) -> bool:
        if not self.get_cur_scope_identifier_container().identifier_exists(identifier):
            return self.global_identifier_container.identifier_exists(identifier)

        return True
    
    def get_identifier_node(self, identifier: str) -> ASTNode:
        node = self.get_cur_scope_identifier_container().get_identifier_node(identifier)
        if node == -1:
            return self.global_identifier_container.get_identifier_node(identifier)
        
        return node
    
    def set_identifier(self, identifier: str, value: ASTNode, force_global: bool = False, is_func=True) -> None:
        if force_global:
            return self.global_identifier_container.set_identifier(identifier, value, is_func=True)
        return self.get_cur_scope_identifier_container().set_identifier(identifier, value, is_func=True)

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
        self.identifier_dict = deepcopy(BUILT_IN_FUNC_DICT)
        self.invalid_identifier_dict = {}
        self.func_identifiers = list(BUILT_IN_FUNC_DICT.keys())

    def get_invalid_identifier(self, name) -> str:
        reverse_inv_ident_dict = {identifier: invalid_identifier for invalid_identifier, identifier in self.invalid_identifier_dict.items()}
        if name not in reverse_inv_ident_dict.keys():
            return name
        
        return reverse_inv_ident_dict[name]

    def identifier_exists(self, identifier: str) -> bool:
        identifier = self.check_invalid_identifier(identifier)
        return identifier in self.identifier_dict.keys()
    
    def get_identifier_node(self, identifier: str) -> ASTNode:
        identifier = self.check_invalid_identifier(identifier)
        if identifier not in self.identifier_dict.keys():
            return -1
        return self.identifier_dict[identifier]
    
    def generate_relative_identifier(self, identifier: str) -> str:
        if identifier in INVALID_IDENTIFIERS:
            new_identifier = "_" + identifier
            while new_identifier in self.identifier_dict:
                new_identifier = "_" + identifier
            
            self.invalid_identifier_dict[new_identifier] = identifier
            return new_identifier

        return identifier
    
    def set_identifier(self, identifier: str, value: ASTNode, is_func=False) -> None:
        if identifier in INVALID_IDENTIFIERS:
            relative_identifier = self.generate_relative_identifier(identifier)
            self.invalid_identifier_dict[identifier] = relative_identifier
            identifier = relative_identifier

            if value:
                value.name = relative_identifier

        identifier = self.check_invalid_identifier(identifier)
        
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