"""
AST Implementation for the Parser of the pytoc Python Transpiler

Implements all necessary nodes and the AST class itself
"""


from __future__ import annotations

class ASTNode():
    def __init__(self):
        """
        Common base class for all nodes

        Attributes:

        parent: Node of which the node is a child
        id: A unique identifier for each node
        repr_offset: The indentation for the __repr__ function
        """
        self.parent = None
        self.id = None
        self.repr_offset = 0

class ASTBaseNode(ASTNode):
    def __init__(self) -> None:
        """
        Functions as the root of the AST, all other nodes are contained in the children of this node
        """
        super().__init__()
        self.children = []

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        child_str = f""
        for child in self.children:
            child.repr_offset = self.repr_offset + 2
            child_str += f"\n{"    " * child.repr_offset}{child}"
            child_str = child_str
        
        return f"Module[\n{tab_offset}    Children[{tab_offset}    {child_str}\n{tab_offset}    ]\n{tab_offset}    Len: {len(self.children)}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class ExpressionNode(ASTNode):
    def __init__(self, op: str) -> None:
        """
        Base Class for all expressions

        Attributes:
    
        left: left side of the expression
        op: operator of the expression
        right: right side of the expression
        type: specified the type of the expression
        """
        super().__init__()
        self.left = None
        self.op = op
        self.right = None
        self.type = None

    def __repr__(self) -> str:
        self.left.repr_offset = self.repr_offset + 2
        self.right.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        return f"ExpressionNode[\n{tab_offset}    Left[ \n{tab_offset}        {self.left}\n{tab_offset}    ]\n{tab_offset}    Operator: '{self.op}'  \n{tab_offset}    Right:[\n{tab_offset}        {self.right}\n{tab_offset}    ]    \n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class NumberNode(ASTNode):
    def __init__(self, value: int | float) -> None:
        """
        Node describing all numerical literals like floats or integers
        """
        super().__init__()
        self.value = value
        self.type = None
        
    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        return f"NumberNode[\n{tab_offset}    Value: {self.value}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class StringNode(ASTNode):
    def __init__(self, value: str) -> None:
        """
        Node describing string literals
        """
        super().__init__()
        self.value = value
        self.type = "str"

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        return f"StringNode[\n{tab_offset}    Value: {self.value}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class BoolNode(ASTNode):
    def __init__(self, value: bool) -> None:
        """
        Node describing boolean literals
        """
        super().__init__()
        self.value = value
        self.type = "bool"

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        return f"BoolNode[\n{tab_offset}    Value: {self.value}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class NoneNode(ASTNode):
    def __init__(self) -> None:
        """
        Node describing the "None" value
        """
        super().__init__()
        self.type = "none"

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        return f"NoneNode[\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class ArrayNode(ASTNode):
    def __init__(self) -> None:
        """
        Node describing list literals, children contains the nodes representing the elements of the list
        """
        super().__init__()
        self.children = []
        self.type = "list"

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        child_str = f""
        for child in self.children:
            child.repr_offset = self.repr_offset + 2
            child_str += f"\n{"    " * child.repr_offset}{child}"
            child_str = child_str
        
        return f"ArrayNode[\n{tab_offset}    Children[{tab_offset}    {child_str}\n{tab_offset}    ]\n{tab_offset}    Len: {len(self.children)}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class VarNode(ASTNode):
    def __init__(self, name: str) -> None:
        """
        Node describing the usage of variable identifiers
        """
        super().__init__()
        self.name = name
        self.type = None

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        return f"VarNode[\n{tab_offset}    Name: {self.name}\n{tab_offset}    Type: {self.type}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class ArrayVarNode(ASTNode):
    def __init__(self, name: str):
        """
        Node representing the usage of variable identifiers combined with an indexing or slice expression
        """
        super().__init__()
        self.name = name
        self.content = None
        self.type = "list"

    def __repr__(self) -> str:
        if self.content:
            self.content.repr_offset = self.repr_offset+2
        tab_offset = "    " * self.repr_offset
        return f"ArrayVarNode[\n{tab_offset}    Name: {self.name}\n{tab_offset}    Content[\n{tab_offset}        {self.content}\n{tab_offset}    ]\n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class SliceExpressionNode(ASTNode):
    def __init__(self) -> None:
        """
        Node representing a slice expression
        """
        super().__init__()
        self.left = None
        self.right = None
        self.type = "int"

    def __repr__(self) -> str:
        if self.left:
            self.left.repr_offset = self.repr_offset + 2
        if self.right:
            self.right.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        return f"SliceExpressionNode[\n{tab_offset}    Left[\n{tab_offset}        {self.left}\n{tab_offset}    ]\n{tab_offset}    Operator: ':'\n{tab_offset}    Right[\n{tab_offset}        {self.right}\n{tab_offset}    ]\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class AssignNode(ASTNode):
    def __init__(self, name: str) -> None:
        """
        Node representing an assignment expression
        children_types is only used if the value type is 'list' and it stores the types of the list elements
        """
        super().__init__()
        self.name = name
        self.value = None
        self.type = None
        self.children_types = []

    def __repr__(self) -> str:
        if self.value:
            self.value.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        return f"AssignNode[\n{tab_offset}    Name: {self.name}\n{tab_offset}    Value[\n{tab_offset}        {self.value}\n{tab_offset}    ]\n{tab_offset}    Type: {self.type}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class BinOpNode(ASTNode):
    def __init__(self, op: str) -> None:
        """
        Node representing a binary operation expression
        """
        super().__init__()
        self.left = None
        self.op = op
        self.right = None
        self.type = None

    def __repr__(self) -> str:
        if self.left:
            self.left.repr_offset = self.repr_offset + 2
        if self.right:
            self.right.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        return f"BinOpNode[\n{tab_offset}    Left[ \n{tab_offset}        {self.left}\n{tab_offset}    ]\n{tab_offset}    Operator: '{self.op}'  \n{tab_offset}    Right:[\n{tab_offset}        {self.right}\n{tab_offset}    ]    \n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class UnOpNode(ASTNode):
    def __init__(self, op: str) -> None:
        """
        Node representing a unary operation expression
        """
        super().__init__()
        self.op = op
        self.right = None
        self.type = None

    def set_type(self, type: str) -> None:
        self.type = type
        return None

    def __repr__(self) -> str:
        if self.right:
            self.right.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        return f"UnOpNode[\n{tab_offset}    Operator: '{self.op}'\n{tab_offset}    Right[\n{tab_offset}        {self.right}\n{tab_offset}    ] \n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class ConditionExpressionNode(ASTNode):
    def __init__(self, op: str) -> None:
        """
        Node representing a conditional expression
        """
        super().__init__()
        self.left = None
        self.op = op
        self.right = None
        self.type = "bool"

    def __repr__(self) -> str:
        self_repr = BinOpNode.__repr__(self)
        self_repr = "ConditionExpressionNode" + self_repr[9:]
        return self_repr

class FuncDefNode(ASTNode):
    def __init__(self, name: str, arg_names: list[str]) -> None:
        """
        Node representing a function definition statement

        Attributes:

        indentation: The indentation level of the block representing the body of the function definition
        arg_names: The identifiers for the arguments taken by the function
        arg_types: The expected types of the arguments taken by the function
        unparsed_children: Contains the unparsed block of tokens representing the body of the function definition until the function is called, specifying the types of the function arguments
        func_call_nodes: Contains the FuncCallNodes representing a call to the function
        var_identifier_dict: Dictionary containing all variable identifiers and their respective AssignNode in the scope of the function body
        return_node: Contains the ReturnNodes found in the function body
        """
        super().__init__()
        self.indentation = None
        self.name = name
        self.arg_names = arg_names
        self.arg_types = None
        self.unparsed_children = None
        self.children = []
        self.func_call_nodes = None
        self.var_identifier_dict = {}
        self.return_type = None
        self.return_node = []

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        child_str = f""
        if self.children:
            child_len = len(self.children)
            for child in self.children:
                if not child: continue
                child.repr_offset = self.repr_offset + 2
                child_str += f"\n{"    " * child.repr_offset}{child}"
        else:
            child_len = 0
        arg_str = ", ".join(self.arg_names)
        
        return f"FuncDefNode[\n{tab_offset}    Name: {self.name}\n{tab_offset}    Args: {arg_str}\n{tab_offset}    Children[{tab_offset}        {child_str}\n{tab_offset}    ]\n{tab_offset}    Len: {child_len}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"
    
class ReturnNode(ASTNode):
    def __init__(self) -> None:
        """
        Node representing a return statement inside a function definition
        """
        super().__init__()
        self.return_value = None
        self.type = None

    def __str__(self) -> str:
        tab_offset = "    " * self.repr_offset
        if self.return_value:
            self.return_value.repr_offset = self.repr_offset + 2
        return f"ReturnNode[\n{tab_offset}    ReturnValue[\n{tab_offset}        {self.return_value}\n{tab_offset}    ]\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class FuncCallNode(ASTNode):
    def __init__(self, name: str) -> None:
        """
        Node representing a call to a function, args represents the arguments passed to the function while type represents the return type of the FuncDefNode associated with the name
        """
        super().__init__()
        self.name = name
        self.args = []
        self.type = None

    def __repr__(self) -> str:
        tab_offset = "    " * self.repr_offset
        arg_str = f""
        if self.args:
            for arg in self.args:
                if not arg: continue
                arg.repr_offset = self.repr_offset + 2
                arg_str += f"\n{"    " * arg.repr_offset}{arg}"
        args_len = len(self.args) if self.args else 0
        
        return f"FuncCallNode[\n{tab_offset}    Name: {self.name}\n{tab_offset}    Args[{tab_offset}        {arg_str}\n{tab_offset}    ]\n{tab_offset}    Len: {args_len}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class ForLoopNode(ASTNode):
    def __init__(self, iter_var_name: str) -> None:
        """
        Node representing a for-loop statement

        Attributes:
        
        iter_var_name: Contains the name of the variable representing the current element of the iteration
        iter_var_type: Contains the type of the variable representing the current element of the iteration
        iter: Contains the Node representing the iterable that the loop iterates over
        """
        super().__init__()
        self.iter_var_name = iter_var_name
        self.iter = None
        self.children = []

    def __repr__(self) -> str:
        if self.iter:
            self.iter.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        child_str = f""
        if self.children:
            for child in self.children:
                if not child: continue
                child.repr_offset = self.repr_offset + 2
                child_str += f"\n{"    " * child.repr_offset}{child}"
        else:
            child_str = "None"
        children_len = len(self.children) if self.children else 0
        
        return f"ForLoopNode[\n{tab_offset}    Iter Var Name: {self.iter_var_name}\n{tab_offset}    Iter[\n{tab_offset}        {self.iter}\n{tab_offset}    Children[{tab_offset}        {child_str}\n{tab_offset}    ]\n{tab_offset}    Len: {children_len}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class WhileLoopNode(ASTNode):
    def __init__(self) -> None:
        """
        Node representing a while-loop statement

        Attributes:

        condition: Contains the ConditionalExpressionNode representing the loop condition
        """
        super().__init__()
        self.condition = None
        self.children = []

    def __repr__(self) -> str:
        if self.condition:
            self.condition.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        child_str = f""
        if self.children:
            for child in self.children:
                if not child: continue
                child.repr_offset = self.repr_offset + 2
                child_str += f"\n{"    " * child.repr_offset}{child}"
            child_len = len(self.children)
            help_str = ""
        else:
            child_str = "None"
            child_len = 0
            help_str = "\n"
        
        return f"WhileLoopNode[\n{tab_offset}    Condition[\n{tab_offset}        {self.condition}\n{tab_offset}    Children[{help_str}{tab_offset}        {child_str}\n{tab_offset}    ]\n{tab_offset}    Len: {child_len}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class IfNode(ASTNode):
    def __init__(self) -> None:
        """
        Node representing an if statement
        """
        super().__init__()
        self.condition = None
        self.children = []

    def __repr__(self) -> str:
        repr_res = WhileLoopNode.__repr__(self)
        repr_res = "IfNod" + repr_res[12:]
        return repr_res

class ElifNode(ASTNode):
    def __init__(self) -> None:
        """
        Node representing an elif statement

        Attributes:

        prev_conditions: Contains the If- and potentially ElifNodes that have occured prior to the current elif statement
        """
        super().__init__()
        self.condition = None
        self.prev_conditions = []
        self.children = []

    def __repr__(self) -> str:
        if self.condition:
            self.condition.repr_offset = self.repr_offset + 2
        tab_offset = "    " * self.repr_offset
        prev_condition_str = f""
        for prev_condition in self.prev_conditions:
            if not prev_condition: continue
            prev_condition.repr_offset = self.repr_offset + 2
            prev_condition_str += f"\n{"    " * prev_condition.repr_offset}{prev_condition}"
        child_str = f""
        for child in self.children:
            if not child: continue
            child.repr_offset = self.repr_offset + 2
            child_str += f"\n{"    " * child.repr_offset}{child}"
        
        return f"ElifNode[\n{tab_offset}    Condition[\n{tab_offset}        {self.condition}\n{tab_offset}    PreviousConditions[\n{tab_offset}        {prev_condition_str}\n{tab_offset}    ]\n{tab_offset}    Children[{tab_offset}        {child_str}\n{tab_offset}    ]\n{tab_offset}    Len: {len(self.children)}\n{tab_offset}    Id: {self.id}\n{tab_offset}]"

class ElseNode(ASTNode):
    def __init__(self) -> None:
        """
        Node representing an else statement
        """
        super().__init__()
        self.condition = None
        self.prev_conditions = []
        self.children = []
        
    def __repr__(self) -> str:
        self_repr = ElifNode.__repr__(self)
        self_repr = "ElseNode" + self_repr[8:]
        return self_repr

class AST():
    def __init__(self) -> None:
        """
        Abstract Syntax Tree for the pytoc Parser:

        Attributes:

        base_node: Root of the AST
        cur_node: Node of the AST that is currently being modified
        next_free_id: Stores the next id that can be assigned to a newly created node
        """
        self.base_node = ASTBaseNode()
        self.base_node.id = 0
        self.cur_node = self.base_node
        self.next_free_id = 1

    def traverse_node(self, trvs_type: str = "children") -> int:
        """
        Purpose: Changes the current node to a node contained in an attribute of the current node

        Takes the name of the attribute of the current node containing the node to which we want to traverse

        Checks that the current node has the specified attribute
        Handles both the case of the attribute to traverse to being a list or just intended for one node
        Sets the current node equal to the node contained in the attribute

        Returns -1 on error, otherwise None
        """
        parent_node = self.cur_node
        if not parent_node.__getattribute__(trvs_type):
            return -1
        
        self.cur_node = parent_node.__getattribute__(trvs_type)
        if isinstance(self.cur_node, list):
            self.cur_node = self.cur_node[0]
        self.cur_node.parent = parent_node
        return 0

    def prev_child_node(self) -> int:
        """
        Purpose: Changes the current node that must be contained in a list to the node with a list index of the index of the current node minus one

        Obtains the parent node of the current node
        Obtains the index of the current node inside the list attribute of the parent node
        Verifies that the current node is not at the start of the list
        Sets the current node to the previous node in the list

        Returns -1 on error, otherwise 0
        """
        parent_node = self.cur_node.parent
        cur_node_idx = parent_node.children.index(self.cur_node)
        if cur_node_idx == 0:
            return -1
        self.cur_node = parent_node.children[cur_node_idx-1]
        self.cur_node.parent = parent_node
        return 0

    def detraverse_node(self) -> None:
        """
        Changes the current node to the parent of the current node
        """
        self.cur_node = self.cur_node.parent
        return None
    
    def traverse_node_by_id(self, id: int, traversal_type: str = "children") -> None:
        """
        Purpose: Same purpose as traverse_node() but with the ability to specify the id of the node in the list that is traversed to

        Takes the id of the child node to be changed to and the name of the attribute containing the target node

        Incase the specified attribute of the current node is not of type list, the current node is set equal to the content of the attribute
        Otherwise we iterate over the children nodes contained in the attribute of the current node until we find a child with the specified id
        If there is no child with the specified id, we raise an Exception

        Returns None
        """
        parent_node = self.cur_node
        traversal_target = parent_node.__getattribute__(traversal_type)
        if not isinstance(traversal_target, list):
            self.cur_node = traversal_target
            if not traversal_target.parent:
                traversal_target.parent = parent_node
            return
        for child in traversal_target:
            if not child.parent:
                child.parent = parent_node
            if child.id == id:
                self.cur_node = child
                return
        raise Exception(f"No Node with id {id} contained in attribute '{traversal_type}' of node {self.cur_node}")

    def append_node(self, node: ASTNode, traversal_type: str = "children") -> int:
        """
        Purpose: Inserts a node into a specidfied attribute of the current node in the ast

        Takes the node to be inserted and the name of the attribute of the current node where the node is to be inserted

        Sets the id of the new node and increments the next free id
        Handles attributes of type list by appending the node to the list representing the attribute
        Handles normal attributes by just setting the attribute equal to the new node

        Returns the id of the new node
        """
        node.parent = self.cur_node
        node.id = self.next_free_id
        self.next_free_id += 1

        cur_value = self.cur_node.__getattribute__(traversal_type)
        if isinstance(cur_value, list):
            self.cur_node.__setattr__(traversal_type, cur_value + [node])
        else:
            self.cur_node.__setattr__(traversal_type, node)
        return node.id
    
    def get_parent_node(self, searched_node: ASTNode) -> ASTNode:
        """
        Purpose: Traverses up the whole ast until it finds a node of the specified type and returns that node

        Takes the type of the node that we are searching for

        Keeps track of the original current node
        Calls detraverse_node() until either a node if the desired type or the ASTBaseNode is reached

        Returns the desired node if it is found, otherwise -1
        """
        old_cur_node = self.cur_node
        while not isinstance(self.cur_node, ASTBaseNode):
            if isinstance(self.cur_node, searched_node):
                node = self.cur_node
                self.cur_node = old_cur_node
                return node
            self.detraverse_node()
        self.cur_node = old_cur_node
        return -1

    def __repr__(self):
        """
        Representation function for the AST
        """
        return self.base_node.__repr__()