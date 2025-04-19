    static Value vsqrt(const Value& val, const int line, const char* func){
        if (val.is<long long>()){
            long double res = sqrtl(val.as<long long>());

            if (std::isnan(res)){
                RunTime instance;
                instance.throw_rt_error("Cannot compute the square root of negative number", line, func);
                return Value(none{});
            }
            return Value(res);
        }
        else if (val.is<long double>()){
            long double res = sqrtl(val.as<long long>());

            if (std::isnan(res)){
                RunTime instance;
                instance.throw_rt_error("Cannot compute the square root of negative number", line, func);
                return Value(none{});
            }
            return Value(res);
        }
        RunTime instance;
        instance.throw_rt_error("Invalid operant type for operation 'sqrt': " + get_dbg_type(val.value) + ", should be 'int' or 'float'", line, func);
        return Value(none{});
    }