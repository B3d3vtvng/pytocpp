"""
Class managing the core functionality of the pytoc Python Transpiler
"""

from src.utils.error import ModuleNotFoundError
from src.lexer import Lexer
from src.parser import Parser
from src.ast_optimization_pass import ASTOptimizationPass
from src.code_generator import CodeGenerator

class Compiler():
    def __init__(self, file_n, flags):
        """
        Attributes:

        flags: The command flags retrieved and passed by the commandline handler
        file_n: The name of the file to be compiled
        new_file_n: The name of the target file
        """
        self.flags = flags
        self.file_n = file_n
        self.validate_file_n()
        self.new_file_n = self.get_new_file_n()

    def validate_file_n(self) -> None:
        try:
            open(self.file_n, "r")
        except Exception:
            print(ModuleNotFoundError(self.file_n[:-3].replace("/", ".")))
            exit(1)

    def get_new_file_n(self):
        """
        Checks if the flag '-b' was passed, indicating that the user specified a name for the target file
        If it was not passed, removes the old file extension from the given file name and replaces it with .cpp

        Returns the target file name
        """
        if not self.flags or "-o" not in self.flags:
            raw_file_n = self.file_n.split('.')[0]
            return raw_file_n+".cpp"
        else:
            return self.flags["-o"]
        
    #wrapper function to handle errors in a clean way :)
    def run_component(self, component: object, function: callable, error_code, haswarning=False) -> any:
        """
        Purpose: Runs a compiler component and checks if errors have occured within and handles them accordingly

        Takes the component, the target function and the error code if an error occures

        Runs the given function\n
        Checks if the error attribute of the component contains something\n
        Prints the content of the error attribute and exits with the given error code if it does\n

        Otherwise returns the output of the function
        """
        output = function()
        if component.error:
            print(component.error)
            print("NOTE: Please note that this tool only supports a subset of the python language - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n")
            exit(error_code)
        
        if haswarning and component.warning and "--disable-w" not in self.flags.keys():
            print(component.warning)
            print("NOTE: Please note that this tool only supports a subset of the python language - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n")
        
        return output
        
    def compile(self):
        """
        Initializes each component of the compiler and runs its main function through run_component()

        Returns 0
        """
        lexer = Lexer(self.file_n)
        tokens = self.run_component(lexer, lexer.make_tokens, 2)
        if "--show-tokens" in self.flags.keys():
            print(tokens)
        parser = Parser(tokens, self.file_n, self.flags)
        ast, func_identifier_dict, var_identifier_dict, invalid_func_identifier_dict, invalid_var_identifier_dict = self.run_component(parser, parser.make_ast, 3, haswarning=True)
        if "--import" in self.flags:
            return ast, func_identifier_dict, var_identifier_dict, invalid_func_identifier_dict, invalid_var_identifier_dict
        ast_optimizer = ASTOptimizationPass(ast, func_identifier_dict)
        ast = self.run_component(ast_optimizer, ast_optimizer.optimize_ast, 4)
        if "--show-ast" in self.flags.keys():
            print(ast)
        code_generator = CodeGenerator(ast, self.new_file_n)
        new_file_n = self.run_component(code_generator, code_generator.generate_code, 5)
        print(f"Sucessfully compiled: {self.file_n} -> {new_file_n}")
        return 0

