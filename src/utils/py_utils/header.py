DEFAULT_HEADER = [
    "//##########################################Header########################################################\n",
    "\n",
    "#include <iostream>\n",
    "#include <variant>\n",
    "#include <string>\n",
    "#include <vector>\n",
    "#include <sstream>\n",
    "\n",
    "class Value;\n",
    "\n",
    "using none = std::monostate;\n",
    "using value_t = std::variant<int, float, bool, std::string, std::vector<Value>, none>;\n",
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
    "        std::cout << __FILE__ << \" : RuntimeError: \" << error_msg << \"\\n\";\n",
    "        exit(1);\n",
    "    }\n",
    "};\n",
    "\n",
    "//#############################################User Programm#################################################\n"
]

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
    "vsub"
]

VALUE_INSERT_LINE = 26

RUNTIME_INSERT_LINE = 35

OPERATOR_TO_MODULE_DICT = {
    "!=": "vnequ",
    "+": "vadd",
    "and": "vand",
    "/": "vdiv",
    "==": "vequ",
    "*": "vmul",
    "or": "vor",
    "-": "vsub"
}

BUILT_IN_FUNC_TO_MODULE_DICT = {
    "str": "tostr",
    "input": "vinput",
    "len": "vlen",
    "print": "vprint",
    "range": "vrange"
}

