    static Value vnot(const Value& val, const int line, const char* func){
        if (!val.is<bool>()){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool', not " + get_dbg_type(val), line, func);
            return Value(none{});
        }

        return Value(!val.as<bool>());
    }
