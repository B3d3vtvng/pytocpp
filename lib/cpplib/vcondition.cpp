    static bool vcondition(const Value& condition, const int line, const char* func){
        if (!std::holds_alternative<bool>(condition.get_value())){
            RunTime instance;
            instance.throw_rt_error("Invalid type for conditional expression: " + get_dbg_type(condition.get_value()) + ", should be: 'bool'", line, func);
            return false;
        }

        return std::get<bool>(condition.get_value());
    }
