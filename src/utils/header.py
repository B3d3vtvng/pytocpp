DEFAULT_HEADER = [
    "//##########################################Header########################################################\n",
    "\n",
    "#include <iostream>\n",
    "#include <variant>\n",
    "#include <string>\n",
    "#include <vector>\n",
    "\n",
    "class Value;\n",
    "\n",
    "using none = std::monostate;\n",
    "using value_t = std::variant<long long, long double, bool, std::string, std::vector<Value>, none>;\n",
    "\n",
    "enum Compare{\n",
    "    GREATER,\n",
    "    LESS,\n",
    "    GEQU,\n",
    "    LEQU\n",
    "};\n",
    "\n",
    "using cmp_t  = Compare;\n",
    "\n",
    "class Value {\n",
    "private:\n",
    "    value_t value;\n",
    "\n",
    "public:\n",
    "    Value(value_t new_value){\n",
    "        value = new_value;\n",
    "    }\n",
    "\n",
    "    value_t get_value() const {\n",
    "        return value;\n",
    "    }\n",
    "\n",
    "};\n",
    "\n",
    "\n",
    "class RunTime {\n",
    "private:\n",
    "    void throw_rt_error(const std::string& error_msg) const{\n",
    "        std::cout << \"\\n\" << __FILE__ << \": RuntimeError: \" << error_msg << \"\\n\\n\" << \"NOTE: Please note that this tool only supports a subset of the python language - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\\n\\n\";\n",
    "        exit(1);\n",
    "    }\n",
    "};\n",
    "\n",
    "//#############################################User Programm#################################################\n"
]

MAIN_WRAPPER = """int main(int __argc, char** __argv){
    Value argc = Value(__argc);
    Value argv = Value([__argc, __argv]() {
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

VALUE_INSERT_LINE = 33

RUNTIME_INSERT_LINE = 43

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
    "sleep": "sleep"
}

INVALID_VAR_NAMES = [
    "__argc",
    "__argv",
    "__restrict__",
    "int",
    "long",
    "unsigned",
    "signed",
    "char",
    "float",
    "double"
]

INVALID_FUNC_NAMES = [
    "main"
]

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
    "sleep": ("chrono", "thread")
}

STDLIB_TO_MODULE_PATH_DICT = {
    "os.py": "lib/pylib/os.py"
}

