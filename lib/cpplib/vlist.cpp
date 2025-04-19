    static Value vlist(const Value& str_input, const int line, const char* func){
        if (!str_input.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for built-in function list(): " + get_dbg_type(str_input) + ", should be: 'str'", line, func);
            return Value(none{});
        }

        std::string& input = std_input.as<std::string>();
        std::vector<Value>& result_vec;
        for (char chr : input) {
            result_vec.emplace_back(Value(std::string(1, chr)));
        }

        return Value(result_vec);
    }