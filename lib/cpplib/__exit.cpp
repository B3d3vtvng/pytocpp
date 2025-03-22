    static void __exit(const Value& exit_code_v, const int line, const char* func){
        value_t exit_code = exit_code_v.get_value();
        if (!std::holds_alternative<long long>(exit_code)){
            RunTime instance;
            instance.throw_rt_error("Invalid type for return code", line, func);
            return;
        }
        exit(std::get<long long>(exit_code));
    }