    static Value vindex(const Value& iterable_v, const Value& index_v){
        value_t iterable = iterable_v.get_value();
        value_t index = index_v.get_value();

        if (!std::holds_alternative<int>(index)){
            RunTime instance;
            instance.throw_rt_error("Indexing expressions must be of type 'int'");
            return Value(none{});
        }

        if (std::holds_alternative<std::vector<Value> >(iterable)){
            int int_index = std::get<int>(index);

            if (int_index >= std::get<std::vector<Value> >(iterable).size() | int_index < 0){
                RunTime instance;
                instance.throw_rt_error("List index out of range");
                return Value(none{});
            }
            return std::get<std::vector<Value> >(iterable)[int_index];
        }
        else if (std::holds_alternative<std::string>(iterable)){
            int int_index = std::get<int>(index);

            if (int_index >= std::get<std::string>(iterable).length() | int_index < 0){
                RunTime instance;
                instance.throw_rt_error("List index out of range");
                return Value(none{});
            }
            return Value(std::get<std::string>(iterable)[int_index]);
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot index a non-container type");
            return Value(none{});
        }
    }
