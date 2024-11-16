    static Value vstrip(const Value& str_v, const Value& strip_v){
        value_t str_vt = str_v.get_value();
        value_t strip_vt = strip_v.get_value();

        if (!std::holds_alternative<std::string>(str_vt) | !std::holds_alternative<std::string>(strip_vt)){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for function strip()");
            return Value(none{});
        }

        std::string str = std::get<std::string>(str_vt);
        std::string strip = std::get<std::string>(strip_vt);
        std::string new_string = "";

        if (strip.length() != 1){
            RunTime instance;
            instance.throw_rt_error("Cannot strip more than one character");
            return Value(none{});
        }

        for (const char character : str){
            if (character != strip[0]){
                new_string += character;
            }
        }

        return Value(new_string);
    }
