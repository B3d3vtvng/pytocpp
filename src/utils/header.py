with open("lib/cpplib/default_header.cpp") as file:
    DEFAULT_HEADER = file.readlines()

DEFAULT_GLOBS = "Value argc;\nValue argv;\n"

MAIN_WRAPPER = """int main(int __argc, char** __argv){
    argc = Value(__argc);
    argv = Value([__argc, __argv]() {
        std::vector<Value> _argv;
        for (int i = 0; i < __argc; ++i) {
            _argv.emplace_back(Value(__argv[i]));
        }
        return _argv;
    }());

%
    return 0;
}"""

HEADER_MODULES = [
    "compare_enum",
    "tostr",
    "v_dequ",
    "v_nequ",
    "v_tostr",
    "vadd",
    "validate_iter",
    "vand",
    "vcompare",
    "vdiv",
    "vequ",
    "vindex",
    "vinput",
    "vlen",
    "vmul",
    "vneg",
    "vnot",
    "vor",
    "vprint",
    "vrange",
    "vslice",
    "vsub",
    "vmod",
    "vfloat",
]

INCLUDE_INSERT_LINE = 5

VALUE_INSERT_LINE = 49

RUNTIME_INSERT_LINE = 65

OPERATOR_TO_MODULE_DICT = {
    "!=": "vnequ",
    "+": "vadd",
    "and": "vand",
    "/": "vdiv",
    "==": "vequ",
    "*": "vmul",
    "or": "vor",
    "-": "vsub",
    "%": "vmod",
    "<": "vcompare",
    ">": "vcompare",
    "<=": "vcompare",
    ">=": "vcompare"
}

BUILT_IN_FUNC_TO_MODULE_DICT = {
    "int": "toint",
    "str": "tostr",
    "input": "vinput",
    "len": "vlen",
    "print": "vprint",
    "range": "vrange",
    "strip": "vstrip",
    "float": "vfloat",
    "sqrt": "vsqrt",
    "fread": "fread",
    "freadlines": "freadlines",
    "fcreate": "fcreate",
    "fwrite": "fwrite",
    "fwritelines": "fwritelines",
    "exit": "__exit",
    "list": "vlist",
    "os_run": "os_run",
    "sleep": "sleep",
    "time": "time",
    "time_str": "time_str"
}

#Invalid identifiers taken from the shedskin project (https://github.com/shedskin/shedskin/blob/master/shedskin/resources/illegal/illegal.txt)
with open("src/utils/invalid.txt", "r") as invalids:
    INVALID_IDENTIFIERS = invalids.readlines()
    

BUILT_IN_FUNC_TO_LIB_DICT = {
    "v_tostr": ("sstream",),
    "vprint": ("sstream",),
    "vsqrt": ("cmath",),
    "fread": ("fstream",),
    "freadlines": ("fstream",),
    "fcreate": ("fstream",),
    "fwrite": ("fstream",),
    "fwritelines": ("fstream",),
    "os_run": ("cstdlib",),
    "sleep": ("chrono", "thread"),
    "time": ("chrono",),
    "time_str": ("chrono", "sstream", "iomanip"),
    "validate_conditional": ("array",),
}

STDLIB_TO_MODULE_PATH_DICT = {
    "os.py": "lib/pylib/os.py",
    "math.py": "lib/pylib/math.py",
    "timedexec.py": "lib/pylib/timedexec.py"
}

