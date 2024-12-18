    static bool vcondition(const Value& condition){
        if (!std::holds_alternative<bool>(condition.get_value())){
            RunTime instance;
            instance.throw_rt_error("Invalid type for conditional expression");
            return false;
        }

        return std::get<bool>(condition.get_value());
    }
