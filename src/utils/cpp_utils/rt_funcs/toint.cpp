    static Value tostr(const Value& val){
        return Value(val.tostr());
    }

    static Value toint(const Value& val_v){
        const value_t raw_val = val_v.get_value();

        std::string val;
        if (std::holds_alternative<int>(raw_val)){
            return val_v;
        }
        else if (std::holds_alternative<float>(raw_val)){
            const float val = std::get<float>(raw_val);

            return Value(std::round(val));
        }
        else if (std::holds_alternative<std::string>(raw_val)){
            val = std::get<std::string>(raw_val);
        }

        int int_val;
        try{
            int_val = std::stoi(val);
        }
        catch (...){
            RunTime instance;
            instance.throw_rt_error("Cannot convert non-digit to int");
            return Value(none{});
        }

        return Value(int_val);
    }
