from src.utils.py_utils.error import FileError, FlagError
import sys

HELP_MSG = "Usage: python3 main.py [flags (flag args)] [target filename]"
FLAGS = ["--show-ast", "--show-tokens", "-o", "-v"]


class CommandlineHandler():
    def __init__(self):
        self.argv = sys.argv[1:]
        self.error = None

    def handle_args(self):
        if self.argv == []:
            self.error = FileError("No file is specified!", "")
            return None, None
        if self.argv[0] == "--help":
            self.error = HELP_MSG
            return None, None
        try:
            open(self.argv[-1], "r")
        except Exception:
            self.error = FileError("The given file was not found", self.argv[-1])
            return None, None
        if len(self.argv) == 1:
            return self.argv[0], {}
        file_n = self.argv.pop(-1)
        flags = {}
        for i, arg in enumerate(self.argv):
            if arg in FLAGS:
                flags[arg] = None
            else:
                if i == 0 or self.argv[i-1] not in FLAGS:
                    self.error = FlagError("InvalidFlagError", f"Invalid Flag: {arg}")
                    return None, None
                flags[self.argv[i-1]] = arg

        return file_n, flags
        