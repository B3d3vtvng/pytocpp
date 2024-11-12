    static Value vlen(const Value& container_v){
        value_t container = container_v.get_value();

        if (std::holds_alternative<std::vector<Value> >(container)){
            return Value(static_cast<int>(std::get<std::vector<Value> >(container).size()));
        }
        else if (std::holds_alternative<std::string >(container)){
            return Value(static_cast<int>(std::get<std::string>(container).length()));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot determine length of variable of a non-container type");
            return Value(none{});
        }
    }
