    static Value vstrip(const Value& str, const Value& strip, const int line, const char* func){
        if (!str_vt.is<std::string>() | !strip_vt.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for function strip(): strip(" + get_dbg_type(str_vt.value) + ", " + get_dbg_type(strip_vt) + "), should be: strip('str', 'str')", line, func);
            return Value(none{});
        }

        std::string& str = str_vt.as<std::string>();
        std::string& strip = strip_vt.as<std::string>();
        std::string& new_string = "";

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
