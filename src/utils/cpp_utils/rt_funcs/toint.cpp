    static Value toint(const Value& val_v){
        const value_t raw_val = val_v.get_value();

        std::string val;
        if (std::holds_alternative<long long>(raw_val)){
            return val_v;
        }
        else if (std::holds_alternative<long double>(raw_val)){
            const long double val = std::get<long double>(raw_val);

            return Value(static_cast<long long>(std::round(val)));
        }
        else if (std::holds_alternative<std::string>(raw_val)){
            val = std::get<std::string>(raw_val);
        }

        int int_val;
        try{
            int_val = std::stoll(val);
        }
        catch (...){
            RunTime instance;
            instance.throw_rt_error("Cannot convert non-digit to int");
            return Value(none{});
        }

        return Value(int_val);
    }
