    static Value vnot(const Value& val_v){
        value_t val = val_v.get_value();

        if (!std::holds_alternative<bool>(val)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'");
            return Value(none{});
        }

        return Value(!std::get<bool>(val));
    }
