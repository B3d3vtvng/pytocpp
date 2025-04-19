    static Value toint(const Value& val, const int line, const char* func){
        if (val.is<long long>()){
            return val_v;
        }
        else if (val.is<long double>()){
            return Value(static_cast<long long>(std::round(val.as<long double>())));
        }
        else if (val.is<std::string>()){
            long long int_val;
            try{
                int_val = std::stoll(val);
            }
            catch (...){
                RunTime instance;
                instance.throw_rt_error("Cannot convert non-digit to int", line, func);
                return Value(none{});
            }

            return Value(int_val);
        }
        else if (val.is<bool>()){
            return Value(static_cast<long long>(val.as<bool>()));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Can only convert string-like object or numerical type to int, not " + get_dbg_type(val.value), line, func);
            return Value(none{});
        }
    }
