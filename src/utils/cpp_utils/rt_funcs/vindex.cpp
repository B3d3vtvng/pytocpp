    static Value vindex(const Value& iterable_v, const Value& index_v){
        value_t iterable = iterable_v.get_value();
        value_t index = index_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iterable)){
            RunTime instance;
            instance.throw_rt_error("A non-iterator cannot be indexed");
            return Value(none{});
        }
        else if (!std::holds_alternative<int>(index)){
            RunTime instance;
            instance.throw_rt_error("Indexing expressions must be of type 'int'");
            return Value(none{});
        }
        else if (std::get<int>(index) < 0 || std::get<int>(index) >= std::get<std::vector<Value> >(iterable).size()){
            RunTime instance;
            instance.throw_rt_error("List index out of bounds");
            return Value(none{});
        }
        return std::get<std::vector<Value> >(iterable)[std::get<int>(index)];
    }
