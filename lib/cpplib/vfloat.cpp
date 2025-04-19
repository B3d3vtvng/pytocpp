    static Value tofloat(const Value& val, const int line, const char* func){
        if (val.is<long long>()){
            long long int_val = val.as<long long>();
            return Value(static_cast<long double>(std::round(int_val)));
        }
        else if (val.is<long double>()){
            return val_v;
        }
        else if (val.is<std::string>()){
            std::string& str_val = val.as<std::string>();
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
        instance.throw_rt_error("Cannot numerical types and str to float, not " + get_dbg_type(val.value), line, func);
        return Value(none{});
    }