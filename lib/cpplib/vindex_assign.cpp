    static Value vindex_assign(const Value& container, const Value& assign, std::vector<Value> idxs, const int line, const char* func){
        if (!idxs[0].is<long long>()){
            RunTime runtime;
            runtime.throw_rt_error("Indexing expressions must be of type int, not " + get_dbg_type(idxs[0].value), line, func);
            return Value(none{});
        }
        long long idx = idxs[0].as<long long>();
        if (container.is<std::vector<Value> >()){
            std::vector<Value> container_vec = container.as<std::vector<Value> >();
            if (idx > container_vec.size()-1 || (idx == 0 && container_vec.size() == 0)){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range", line, func);
                return Value(none{});
            }
            if (idxs.size() == 1){
                container_vec[idx] = assign;
                return Value(container_vec);
            }
            idxs.erase(idxs.begin());
            Value new_vec = vindex_assign(container_vec[idx], assign, idxs, line, func);
            container_vec[idx] = new_vec;
            return Value(container_vec);
        }
        else if (container.is<std::string>()){
            if (!assign.is<std::string>()){
                RunTime runtime;
                runtime.throw_rt_error("Can only assign a value of type string to a string, not " + get_dbg_type(assign.value), line, func);
                return Value(none{});
            }
            std::string container_str = container.as<std::string>();
            if (assign.as<std::string>().length() != 1){
                RunTime runtime;
                runtime.throw_rt_error("Cannot assign non character to index of string object", line, func);
                return Value(none{});
            }
            if (idx > container_str.length()-1){
                RunTime runtime;
                runtime.throw_rt_error("Assignment index out of range", line, func);
                return Value(none{});
            }
            if (idxs.size() == 1){
                container_str.erase(idx, 1);
                container_str.insert(idx, assign.as<std::string>());
                return Value(container_str);
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