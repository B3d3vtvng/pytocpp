    static Value os_run(const Value& command_v, const int line, const char* func){
        value_t command = command_v.get_value();
        if (!std::holds_alternative<std::string>(command)){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for build-in function os_run()", line, func);
            return Value(none{});
        }

        std::string command_str = std::get<std::string>(command);
        long long exit_code = system(command_str.c_str());

        return Value(exit_code);
    }