    [[noreturn]] static void __exit(const Value& exit_code, const int line, const char* func){
        if (!exit_code.is<long long>()){
            RunTime instance;
            instance.throw_rt_error("Invalid type for return code: " + get_dbg_type(exit_code.value) + ", should be: 'int'", line, func);
        }
        exit(exit_code.as<long long>());
    }