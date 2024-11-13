    template<typename... Args>
    static Value vstrip(const Args&... args){
        std::vector<Value> arg_vec = { Value(args)... };

        if (arg_vec.size() == 1){
            value_t str_v = arg_vec[0].get_value();
            value_t strip_v = Value(" ")
        }
        else if (arg_vec.size() == 2){
            value_t str_v = arg_vec[0].get_value()
            value_t strip_v = arg_vec[1].get_value()
        }

        if (!std::holds_alternative<std::string>(str_v) | !std::holds_alternative<std::string>(strip_v)){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for function strip()");
            return Value(none{});
        }

        std::string str = std::get<std::string>(str_v);
        std::string strip = std::get<std::string>(strip);
        std::string new_string = ""

        if (strip.length() != 1){
            RunTime instance;
            instance.throw_rt_error("Cannot strip more than one character");
            return Value(none{});
        }

        for (const char character : str){
            if (character != strip){
                new_string += character;
            }
        }

        return Value(new_string);
    }
