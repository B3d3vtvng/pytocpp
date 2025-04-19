    static std::vector<Value> validate_iter(const Value& iter, const int line, const char* func){
        if (iter.is<std::vector<Value> >()){
            return iter.as<std::vector<Value> >();
        }
        else if (iter.is<std::string>()){
            std::vector<Value> str_vec = std::vector<Value>();
            for (const char chr : iter.as<std::string>()){
                str_vec.push_back(Value(std::string(1, chr)));
            }
            return str_vec;
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot iterate over value of non-container type: " + get_dbg_type(iter.value) + ", should be 'list' or 'str'", line, func);
            return std::vector<Value>{};
        }

    }
