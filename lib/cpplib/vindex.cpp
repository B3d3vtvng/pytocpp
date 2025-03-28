static Value vindex(const Value& container_v, std::vector<Value> idxs_v, const int line, const char* func){
        value_t container = container_v.get_value();
        if (!std::holds_alternative<long long>(idxs_v[0].get_value())){
            RunTime runtime;
            runtime.throw_rt_error("Indexing expressions must be of type int, not " + get_dbg_type(idxs_v[0].get_value()), line, func);
            return Value(none{});
        }
        long long idx = std::get<long long>(idxs_v[0].get_value());
        if (std::holds_alternative<std::vector<Value>  >(container)){
            std::vector<Value> container_vec = std::get<std::vector<Value> >(container);
            if (idx > container_vec.size()-1){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range", line, func);
                return Value(none{});
            }
            if (idxs_v.size() == 1){
                return container_vec[idx];
            }
            idxs_v.erase(idxs_v.begin());
            return vindex(container_vec[idx], idxs_v, line, func);
        }
        else if (std::holds_alternative<std::string>(container_v.get_value())){
            std::string container_str = std::get<std::string>(container_v.get_value());
            if (idx > container_str.length()-1){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range", line, func);
                return Value(none{});
            }
            if (idxs_v.size() == 1){
                return Value(std::string(1, container_str[idx]));
            }
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type: 'char'", line, func);
            return Value(none{});
        }
        else{
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type: " + get_dbg_type(container), line, func);
            return Value(none{});
        }
    }