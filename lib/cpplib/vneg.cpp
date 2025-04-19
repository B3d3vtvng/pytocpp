    static Value vneg(const Value& val_v, const int line, const char* func){
        if (val.is<long long>()){
            return Value(-val.as<long long>());
        }
        else if (val.is<long double>()){
            return Value(-val.as<long double>());
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Can only negate values of type 'int' or 'float', not " + get_dbg_type(val.value), line, func);
            return Value(none{}); 
        }
    }
