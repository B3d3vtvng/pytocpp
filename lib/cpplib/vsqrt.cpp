    static Value vsqrt(const Value& val_v, const int line, const char* func){
        value_t val = val_v.get_value();

        if (std::holds_alternative<long long>(val)){
            long double res = sqrtl(std::get<long long>(val));

            if (std::isnan(res)){
                RunTime instance;
                instance.throw_rt_error("Cannot compute the square root of negative number", line, func);
                return Value(none{});
            }
            return Value(res);
        }
        else if (std::holds_alternative<long double>(val)){
            long double res = sqrtl(std::get<long long>(val));

            if (std::isnan(res)){
                RunTime instance;
                instance.throw_rt_error("Cannot compute the square root of negative number", line, func);
                return Value(none{});
            }
            return Value(res);
        }
        RunTime instance;
        instance.throw_rt_error("Invalid operant type for operation 'sqrt'", line, func);
        return Value(none{});
    }