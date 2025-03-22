    static Value vneg(const Value& val_v, const int line, const char* func){
        value_t val = val_v.get_value();

        if (std::holds_alternative<long long>(val)){
            return Value(-std::get<long long>(val));
        }
        else if (std::holds_alternative<long double>(val)){
            return Value(-std::get<long double>(val));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot negate a value that is not of type 'int' or type 'float'", line, func);
            return Value(none{}); 
        }
    }
