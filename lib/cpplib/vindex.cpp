static Value vindex(const Value& container, std::vector<Value> idxs, const int line, const char* func){
        if (!idxs[0].is<long long>()){
            RunTime runtime;
            runtime.throw_rt_error("Indexing expressions must be of type int, not " + get_dbg_type(idxs[0].value), line, func);
            return Value(none{});
        }
        long long idx = idxs[0].as<long long>();
        if (container.is<std::vector<Value> >()){
            const std::vector<Value>& container_vec = container.as<std::vector<Value> >();
            if (idx > container_vec.size()-1){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range", line, func);
                return Value(none{});
            }
            if (idxs.size() == 1){
                return container_vec[idx];
            }
            idxs.erase(idxs.begin());
            return vindex(container_vec[idx], idxs, line, func);
        }
        else if (container.is<std::string>()){
            const std::string& container_str = container.as<std::string>();
            if (idx > container_str.length()-1){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range", line, func);
                return Value(none{});
            }
            if (idxs.size() == 1){
                return Value(std::string(1, container_str[idx]));
            }
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type: 'char'", line, func);
            return Value(none{});
        }
        else{
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type: " + get_dbg_type(container.value), line, func);
            return Value(none{});
        }
    }