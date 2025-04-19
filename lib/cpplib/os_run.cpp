    static Value os_run(const Value& command, const int line, const char* func){
        if (!command.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for build-in function os_run(): " + get_dbg_type(command.value) + ", should be: 'str'", line, func);
            return Value(none{});
        }
        long long exit_code = system(command.as<std::string>().c_str());

        return Value(exit_code);
    }