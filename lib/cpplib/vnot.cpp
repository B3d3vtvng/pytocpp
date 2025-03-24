    static Value vnot(const Value& val_v, const int line, const char* func){
        value_t val = val_v.get_value();

        if (!std::holds_alternative<bool>(val)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool', not " + get_dbg_type(val), line, func);
            return Value(none{});
        }

        return Value(!std::get<bool>(val));
    }
