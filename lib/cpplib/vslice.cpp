    static Value vslice(const Value &iterable, const Value &slice_left, const Value &slice_right, const int line, const char* func){
        if (!slice_left.is<long long>() || !slice_right.is<long long>()){
            RunTime instance;
            instance.throw_rt_error("Slice expressions must be of type 'int', not [" + get_dbg_type(slice_left) + ":" + get_dbg_type(slice_right) + "]", line, func);
            return Value(none{});
        }

        if (iterable.is<std::vector<Value>>()){
            int vec_len = iterable.as<std::vector<Value>>().size();
            long long slice_left_l = slice_left.as<long long>();
            long long slice_right_l = slice_right.as<long long>();

            if (slice_left_l < 0 || slice_left_l > vec_len-1 || slice_right_l < 0 || slice_right_l > vec_len-1){
                RunTime instance;
                instance.throw_rt_error("Slice index out of bounds", line, func);
                return Value(none{});
            }

            std::vector<Value>& new_iterable;
            std::vector<Value>& iter_vec = iterable.as<std::vector<Value>>();
            for (long long i = slice_left.as<long long>(); i < slice_right.as<long long>(); i++){
                new_iterable.push_back(iter_vec[i]);
            }

            if (slice_left_l == slice_right_l){
                new_iterable = {iter_vec[slice_left_l]};
            }

            return Value(new_iterable);
        }
        else if (iterable.is<std::string>()){
            int str_len = iterable.as<std::string>().length();
            long long slice_left_l = slice_left.as<long long>();
            long long slice_right_l = slice_right.as<long long>();

            if (slice_left_l < 0 || slice_left_l > str_len-1 || slice_right_l < 0 || slice_right_l > str_len-1){
                RunTime instance;
                instance.throw_rt_error("Slice index out of bounds", line, func);
                return Value(none{});
            }

            std::string& new_iterable;
            std::string& iter_str = iterable.as<std::string>();
            for (long long i = slice_left.as<long long>(); i < slice_right.as<long long>(); i++){
                new_iterable += iter_str[i];
            }

            if (slice_left_l == slice_right_l){
                new_iterable = std::string(1, iter_str[slice_left_l]);
            }

            return Value(new_iterable);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Can only index container types, not " + get_dbg_type(iterable.value), line, func);
            return Value(none{});
        }
}
