    static Value vor(const Value& val_1, const Value& val_2, const int line, const char* func){
        if (!val_1.is<bool>() || !val_2.is<bool>()){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool', not " + get_dbg_type(val_1) + " | " + get_dbg_type(val_2), line, func);
            return Value(none{});
        }

        return Value(val_1.as<bool>() || val_2.as<bool>());
    }
