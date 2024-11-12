    static Value vslice(const Value& iterable_v, const Value& slice_left_v, const Value& slice_right_v){
        value_t iterable = iterable_v.get_value();
        value_t slice_left = slice_left_v.get_value();
        value_t slice_right = slice_right_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iterable)){
            RunTime instance;
            instance.throw_rt_error("A non-iterator cannot be indexed");
            return Value(none{});
        }
        else if (!std::holds_alternative<int>(slice_left) || !std::holds_alternative<int>(slice_right)){
            RunTime instance;
            instance.throw_rt_error("Slice expressions must be of type 'int'");
            return Value(none{});
        }
        else if (std::get<int>(slice_left) < 0 || std::get<int>(slice_left) > std::get<std::vector<Value> >(iterable).size() || std::get<int>(slice_right) < 0 || std::get<int>(slice_right) > std::get<std::vector<Value> >(iterable).size()){
            RunTime instance;
            instance.throw_rt_error("Slice index out of bounds");
            return Value(none{});

        }

        std::vector<Value> new_iterable;
        for (int i = std::get<int>(slice_left);i<std::get<int>(slice_right);i++){
            new_iterable.push_back(std::get<std::vector<Value> >(iterable)[i]);
        }
        return Value(new_iterable);
    }
