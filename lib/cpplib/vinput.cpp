    static Value vinput(const Value& msg, const int line, const char* func){
        if (!msg.is<std::string>()){
            RunTime runtime;
            runtime.throw_rt_error("Input message must be of type 'str', not " + get_dbg_type(msg.value), line, func);
            return Value(none{});
        }
        std::cout << msg.as<std::string>();
        std::string input;
        std::getline(std::cin, input);
        return Value(input);
    }
