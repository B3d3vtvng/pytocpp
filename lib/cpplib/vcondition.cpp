    static bool vcondition(const Value& condition, const int line, const char* func){
        if (!condition.is<bool>()){
            RunTime instance;
            instance.throw_rt_error("Invalid type for conditional expression: " + get_dbg_type(condition.value) + ", should be: 'bool'", line, func);
            return false;
        }

        return condition.as<bool>();
    }
