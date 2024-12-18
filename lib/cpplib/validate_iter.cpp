    static std::vector<Value> validate_iter(const Value& iter_v){
        value_t iter = iter_v.get_value();

        if (std::holds_alternative<std::vector<Value> >(iter)){
            return std::get<std::vector<Value> >(iter);
        }
        else if (std::holds_alternative<std::string>(iter)){
            std::vector<Value> str_vec;
            for (const char chr : std::get<std::string>(iter)){
                str_vec.push_back(Value(std::string(1, chr)));
            }
            return str_vec;
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot iterate over value of non-container type");
            return std::vector<Value>{};
        }

    }
