    static Value tofloat(const Value& val_v, const int line, const char* func){
        value_t val = val_v.get_value();

        if (std::holds_alternative<long long>(val)){
            long long int_val = std::get<long long>(val);
            return Value(static_cast<long double>(int_val));
        }
        else if (std::holds_alternative<long double>(val)){
            return val_v;
        }
        else if (std::holds_alternative<std::string>(val)){
            std::string str_val = std::get<std::string>(val);
            try{
                long double float_val = std::stof(str_val);
                return Value(float_val);
            }
            catch (...){
                RunTime instance;
                instance.throw_rt_error("Cannot convert non-digit to float", line, func);
                return Value(none{});
            }
        }
        RunTime instance;
        instance.throw_rt_error("Cannot convert non_numerical type or string type to float", line, func);
        return Value(none{});
    }