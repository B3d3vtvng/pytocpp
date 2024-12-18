"""
Errors for the pytoc Python Transpiler
"""

class Error():
    def __init__(self, error_t, error_v, error_ln, file_n):
        """
        Attributes:

        error_t: The type of the error
        error_v: The message displayed with the error
        error_ln: The line where the error has occured
        file_n: The name of the file where the error has occured
        """
        self.error_t = error_t
        self.error_v = error_v
        self.error_ln = error_ln
        self.file_n = file_n

    def __str__(self):
        return f"\n{self.file_n}:{self.error_ln}  {self.error_t}: {self.error_v}\n"
    

class Warning(Error):
    def __init__(self, warning_v, warning_ln, file_n) -> None:
        super().__init__("Warning", warning_v, warning_ln, file_n)
    
class FileError(Error):
    """
    Error to describe errors concerning files
    """
    def __init__(self, error_v: str, file_n: str) -> None:
        super().__init__("FileError", error_v, -1, file_n)

    def __repr__(self):
        return f"\nFileError: {self.error_v}    File: {self.file_n}\n"
    
class ModuleNotFoundError(Error):
    def __init__(self, file_n) -> None:
        super().__init__("ModuleNotFoundError", "The given module could not be found", -1, file_n)
    
class FlagError():
    """
    Error to describe errors concerning invalid syntax in commandline arguments
    """
    def __init__(self, error_t, error_v):
        self.error_t = error_t
        self.error_v = error_v

    def __str__(self):
        return f"\n{self.error_t}: {self.error_v}\n"
    

class SyntaxError(Error):
    """
    Error to describe errors concerning syntax
    """
    def __init__(self, error_v, error_ln, file_n):
        super().__init__("SyntaxError", error_v, error_ln, file_n)
    
class IndentationError(Error):
    """
    Error to describe errors concerning Indentation"""
    def __init__(self, error_v: str, error_ln: int, file_n: str) -> None:
        super().__init__("IndentationError", error_v, error_ln, file_n)

class TypeError(Error):
    """
    Error to describe errors concerning invalid types
    """
    def __init__(self, error_v, error_ln, file_n) -> None:
        super().__init__("TypeError", error_v, error_ln, file_n)

class NameError(Error):
    """
    Error to describe errors concerning undefined identifiers
    """
    def __init__(self, error_v, error_ln, file_n) -> None:
        super().__init__("NameError", error_v, error_ln, file_n)

class SizeError(Error):
    """
    Error to describe numbers exeeding the supported integer limit
    """
    def __init__(self, error_v, error_ln, file_n) -> None:
        super().__init__("SizeError", error_v, error_ln, file_n)