    static Value vneg(const Value& val_v){
        value_t val = val_v.get_value();

        if (std::holds_alternative<int>(val)){
            return Value(-std::get<int>(val));
        }
        else if (std::holds_alternative<float>(val)){
            return Value(-std::get<float>(val));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot negate a value that is not of type 'int' or type 'float'");
            return Value(none{}); 
        }
    }
