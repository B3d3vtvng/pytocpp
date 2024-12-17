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
    try:
        compiler = Compiler(file_n, flags)
        compiler.compile()
        return 0
    except RecursionError as e:
        print("RecursionError: The given programm causes an infinite recusion loop, most likely due to circular imports")
        if "-v" in flags.keys():
            raise e
        else:
            exit(1)
    except Exception as e:
        if "-v" in flags.keys():
            raise e
        else:
            print("\nAn unknown error has occured, please use -v flag for a more detailed error message\n")
            return 1

return_code = compile()
exit(return_code)