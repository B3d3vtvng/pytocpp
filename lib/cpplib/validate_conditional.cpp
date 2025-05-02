    static Value validate_conditional(const int line, const char* func, const char* name, const Value& conditional){
        if (conditional.is<invalid>()){
            RunTime instance;
            instance.throw_rt_error("RunTime Error: Undefined Identifier: " + std::string(name), line, func);
        }
        return conditional;
    }