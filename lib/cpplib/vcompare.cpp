    static Value vcompare(const Value& val_1, const Value& val_2, const cmp_t& compare_type, const int line, const char* func){
        if (val_1.is<long long>() && val_2.is<long long>()) {
            if (compare_type == GREATER){
                return Value(val_1.as<long long>() > val_2.as<long long>());
            }
            else if (compare_type == LESS){
                return Value(val_1.as<long long>() < val_2.as<long long>());
            }
            else if (compare_type == GEQU){
                return Value(val_1.as<long long>() >= val_2.as<long long>());
            }
            else{
                return Value(val_1.as<long long>() <= val_2.as<long long>());
            }
        }
        else if (val_1.is<long long>() && val_2.is<long double>()) {
            if (compare_type == GREATER){
                return Value(val_1.as<long long>() > val_2.as<long double>());
            }
            else if (compare_type == LESS){
                return Value(val_1.as<long long>() < val_2.as<long double>());
            }
            else if (compare_type == GEQU){
                return Value(val_1.as<long long>() >= val_2.as<long double>());
            }
            else{
                return Value(val_1.as<long long>() <= val_2.as<long double>());
            }
        }
        else if (val_1.is<long double>() && val_2.is<long long>()) {
            if (compare_type == GREATER){
                return Value(val_1.as<long double>() > val_2.as<long long>());
            }
            else if (compare_type == LESS){
                return Value(val_1.as<long double>() < val_2.as<long long>());
            }
            else if (compare_type == GEQU){
                return Value(val_1.as<long double>() >= val_2.as<long long>());
            }
            else{
                return Value(val_1.as<long double>() <= val_2.as<long long>());
            }
        }
        else if (val_1.is<long double>() && val_2.is<long double>()) {
            if (compare_type == GREATER){
                return Value(val_1.as<long double>() > val_2.as<long double>());
            }
            else if (compare_type == LESS){
                return Value(val_1.as<long double>() < val_2.as<long double>());
            }
            else if (compare_type == GEQU){
                return Value(val_1.as<long double>() >= val_2.as<long double>());
            }
            else{
                return Value(val_1.as<long double>() <= val_2.as<long double>());
            }
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Invalid type for comparison: " + get_dbg_type(val_1.value) + " compared to " + get_dbg_type(val_2.value), line, func);
            return Value(none{});
        }
    }
