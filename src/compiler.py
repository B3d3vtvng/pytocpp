"""
Class managing the core functionality of the pytoc Python Transpiler
"""

from src.utils.error import ModuleNotFoundError
from src.lexer import Lexer
from src.parser import Parser
from src.ast_optimization_pass import ASTOptimizationPass
from src.code_generator import CodeGenerator
from typing import Any

import sys

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
    def run_component(self, component: object, function: callable, error_code, haswarning=False) -> Any:
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
            print(component.error, file=sys.stderr)
            print("NOTE: Please note that this tool only supports a subset of the python language - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n", file=sys.stderr)
            exit(error_code)
        
        if haswarning and component.warning and "--disable-w" not in self.flags.keys():
            print(component.warning, file=sys.stderr)
            print("NOTE: Please note that this tool only supports a subset of the python language - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n", file=sys.stderr)
        
        return output
    
    def handle_logging(self, component: object, component_output: Any) -> None:
        if "--import" in self.flags: return None

        if component == Lexer:
            if "-v" in self.flags or "--show-tokens" in self.flags:
                print("Generated tokens:\n" + component_output.__str__() + "\n")
            if "--log" in self.flags:
                with open(self.flags["--log"], "w") as log_file:
                    log_file.write(f"Log for the pytocpp transpilation process of file '{self.file_n}':\n\n" + "Generated tokens:\n" + component_output.__str__() + "\n\n")
            
            return None
        
        if "-v" in self.flags or "--show-ast" in self.flags:
            print("Generated ast:\n" + component_output.__str__() + "\n")
        if "--log" in self.flags:
            with open(self.flags["--log"], "a") as log_file:
                log_file.write("Generated ast:\n" + component_output.__str__() + "\n\n")

        return None
        
    def compile(self):
        """
        Initializes each component of the compiler and runs its main function through run_component()

        Returns 0
        """
        lexer = Lexer(self.file_n)
        tokens = self.run_component(lexer, lexer.make_tokens, 2)
        self.handle_logging(Lexer, tokens)

        parser = Parser(tokens, self.file_n, self.flags)
        ast, identifier_manager, special_globals = self.run_component(parser, parser.make_ast, 3, haswarning=True)
        if "--import" in self.flags:
            return ast, identifier_manager, special_globals
        
        ast_optimizer = ASTOptimizationPass(ast, identifier_manager)
        ast = self.run_component(ast_optimizer, ast_optimizer.optimize_ast, 4)
        self.handle_logging(Parser, ast)

        code_generator = CodeGenerator(ast, self.new_file_n, identifier_manager, special_globals, self.file_n)
        new_file_n = self.run_component(code_generator, code_generator.generate_code, 5)

        if "--no-out" not in self.flags.keys():
            print(f"Sucessfully transpiled: {self.file_n} -> {new_file_n}")

        return 0

