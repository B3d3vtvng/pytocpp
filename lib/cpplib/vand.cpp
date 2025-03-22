    static Value vand(const Value& val_1_v, const Value& val_2_v, const int line, const char* func){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (!std::holds_alternative<bool>(val_1) || !std::holds_alternative<bool>(val_2)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'", line, func);
            return Value(none{});
        }

        return Value(std::get<bool>(val_1) && std::get<bool>(val_2));
    }
