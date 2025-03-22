    static Value vindex_assign(const Value& container_v, const Value& assign, std::vector<Value> idxs_v){
        value_t container = container_v.get_value();
        if (!std::holds_alternative<long long>(idxs_v[0].get_value())){
            RunTime runtime;
            runtime.throw_rt_error("Indexing expressions must be of type int!");
            return Value(none{});
        }
        long long idx = std::get<long long>(idxs_v[0].get_value());
        if (std::holds_alternative<std::vector<Value>  >(container)){
            std::vector<Value> container_vec = std::get<std::vector<Value> >(container);
            if (idx > container_vec.size()-1){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range");
                return Value(none{});
            }
            if (idxs_v.size() == 1){
                container_vec[idx] = assign;
                return Value(container_vec);
            }
            idxs_v.erase(idxs_v.begin());
            Value new_vec = vindex_assign(container_vec[idx], assign, idxs_v);
            container_vec[idx] = new_vec;
            return Value(container_vec);
        }
        else if (std::holds_alternative<std::string>(container_v.get_value())){
            if (!std::holds_alternative<std::string>(assign.get_value())){
                RunTime runtime;
                runtime.throw_rt_error("Can only assign a value of type string to a string");
                return Value(none{});
            }
            std::string container_str = std::get<std::string>(container_v.get_value());
            if (std::get<std::string>(assign.get_value()).length() != 1){
                RunTime runtime;
                runtime.throw_rt_error("Cannot assign non character to index of string object");
                return Value(none{});
            }
            if (idx > container_str.length()-1){
                RunTime runtime;
                runtime.throw_rt_error("Indexing expressions must be of type int!");
                return Value(none{});
            }
            if (idxs_v.size() == 1){
                container_str.erase(idx, 1);
                container_str.insert(idx, std::get<std::string>(assign.get_value()));
                return Value(container_str);
            }
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type");
            return Value(none{});
        }
        else{
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type");
            return Value(none{});
        }
    }