    static Value vcompare(const Value& val_1_v, const Value& val_2_v, const cmp_t& compare_type, const int line, const char* func){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<long long>(val_1) && std::holds_alternative<long long>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<long long>(val_1) > std::get<long long>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<long long>(val_1) < std::get<long long>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<long long>(val_1) >= std::get<long long>(val_2));
            }
            else{
                return Value(std::get<long long>(val_1) <= std::get<long long>(val_2));
            }
        }
        else if (std::holds_alternative<long long>(val_1) && std::holds_alternative<long double>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<long long>(val_1) > std::get<long double>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<long long>(val_1) < std::get<long double>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<long long>(val_1) >= std::get<long double>(val_2));
            }
            else{
                return Value(std::get<long long>(val_1) <= std::get<long double>(val_2));
            }
        }
        else if (std::holds_alternative<long double>(val_1) && std::holds_alternative<long long>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<long double>(val_1) > std::get<long long>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<long double>(val_1) < std::get<long long>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<long double>(val_1) >= std::get<long long>(val_2));
            }
            else{
                return Value(std::get<long double>(val_1) <= std::get<long long>(val_2));
            }
        }
        else if (std::holds_alternative<long double>(val_1) && std::holds_alternative<long double>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<long double>(val_1) > std::get<long double>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<long double>(val_1) < std::get<long double>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<long double>(val_1) >= std::get<long double>(val_2));
            }
            else{
                return Value(std::get<long double>(val_1) <= std::get<long double>(val_2));
            }
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Invalid type for comparison", line, func);
            return Value(none{});
        }
    }
