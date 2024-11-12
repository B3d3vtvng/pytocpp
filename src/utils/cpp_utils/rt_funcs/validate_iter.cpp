    static std::vector<Value> validate_iter(const Value iter_v){
        value_t iter = iter_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iter)){
            RunTime instance;
            instance.throw_rt_error("Cannot iterate over value of non-container type");
            return std::vector<Value>{};
        }

        return std::get<std::vector<Value> >(iter);
    }
