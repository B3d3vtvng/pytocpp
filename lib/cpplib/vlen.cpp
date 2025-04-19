    static Value vlen(const Value& container, const int line, const char* func){
        if (container.is<std::vector<Value> >()){
            return Value(static_cast<long long>(container.as<std::vector<Value> >.size()));
        }
        else if (container.is<std::string>()){
            return Value(static_cast<long long>(container.as<std::string>().length()));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot determine length of variable of a non-container type: " + get_dbg_type(container.value), line, func);
            return Value(none{});
        }
    }
