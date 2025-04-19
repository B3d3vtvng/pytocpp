    static Value vstrip(const Value& str_v, const Value& strip_v, const int line, const char* func){
        if (!str_v.is<std::string>() | !strip_v.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for function strip(): strip(" + get_dbg_type(str_v.value) + ", " + get_dbg_type(strip_v.value) + "), should be: strip('str', 'str')", line, func);
            return Value(none{});
        }

        const std::string& str = str_v.as<std::string>();
        const std::string& strip = strip_v.as<std::string>();
        std::string new_string = "";

        if (strip.length() != 1){
            RunTime instance;
            instance.throw_rt_error("Cannot strip more than one character", line, func);
            return Value(none{});
        }

        for (const char character : str){
            if (character != strip[0]){
                new_string += character;
            }
        }

        return Value(new_string);
    }
