    static Value vslice(const Value &iterable_v, const Value &slice_left_v, const Value &slice_right_v, const int line, const char* func){
        value_t iterable = iterable_v.get_value();
        value_t slice_left = slice_left_v.get_value();
        value_t slice_right = slice_right_v.get_value();

        if (!std::holds_alternative<long long>(slice_left) || !std::holds_alternative<long long>(slice_right)){
            RunTime instance;
            instance.throw_rt_error("Slice expressions must be of type 'int', not [" + get_dbg_type(slice_left) + ":" + get_dbg_type(slice_right) + "]", line, func);
            return Value(none{});
        }

        if (std::holds_alternative<std::vector<Value>>(iterable)){
            int vec_len = std::get<std::vector<Value>>(iterable).size();
            long long slice_left_l = std::get<long long>(slice_left);
            long long slice_right_l = std::get<long long>(slice_right);

            if (slice_left_l < 0 || slice_left_l > vec_len-1 || slice_right_l < 0 || slice_right_l > vec_len-1){
                RunTime instance;
                instance.throw_rt_error("Slice index out of bounds", line, func);
                return Value(none{});
            }

            std::vector<Value> new_iterable;
            std::vector<Value> iter_vec = std::get<std::vector<Value>>(iterable);
            for (long long i = std::get<long long>(slice_left); i < std::get<long long>(slice_right); i++){
                new_iterable.push_back(iter_vec[i]);
            }

            if (slice_left_l == slice_right_l){
                new_iterable = {iter_vec[slice_left_l]};
            }

            return Value(new_iterable);
        }
        else if (std::holds_alternative<std::string>(iterable)){
            int str_len = std::get<std::string>(iterable).length();
            long long slice_left_l = std::get<long long>(slice_left);
            long long slice_right_l = std::get<long long>(slice_right);

            if (slice_left_l < 0 || slice_left_l > str_len-1 || slice_right_l < 0 || slice_right_l > str_len-1){
                RunTime instance;
                instance.throw_rt_error("Slice index out of bounds", line, func);
                return Value(none{});
            }

            std::string new_iterable;
            std::string iter_str = std::get<std::string>(iterable);
            for (long long i = std::get<long long>(slice_left); i < std::get<long long>(slice_right); i++){
                new_iterable += iter_str[i];
            }

            if (slice_left_l == slice_right_l){
                new_iterable = std::string(1, iter_str[slice_left_l]);
            }

            return Value(new_iterable);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Can only index container types, not " + get_dbg_type(iterable), line, func);
            return Value(none{});
        }
}
