from src.cmdl_handler import CommandlineHandler
from src.compiler import Compiler

def compile():
    """
    First function to be called in the whole program, 
    initiates the Commandline Handler, 
    retrieves the name of the target file and flags
    and starts the compiler
    """
    cmdl_handler = CommandlineHandler()
    file_n, flags = cmdl_handler.handle_args()
    if cmdl_handler.error:
        print(cmdl_handler.error)
        return 1
    compiler = Compiler(file_n, flags)
    compiler.compile()
    print("Sucess!")
    return 0

return_code = compile()
exit(return_code)