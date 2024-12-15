    static Value vlist(const Value str_input_v){
        value_t str_input = str_input_v.get_value();
        if (!std::holds_alternative<std::string>(str_input)){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for built-in function list()");
            return Value(none{});
        }

        std::string input = std::get<std::string>(str_input);
        std::vector<Value> result_vec;
        for (char chr : input) {
            result_vec.emplace_back(Value(std::string(1, chr)));
        }

        return Value(result_vec);
    }