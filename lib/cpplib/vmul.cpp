    static Value vmul(const Value& val_1, const Value& val_2, const int line, const char* func) {
        if (val_1.is<long long>() && val_2.is<long long>()) {
            long long raw_res = val_1.as<long long>() * val_2.as<long long>();
            return Value(raw_res);
        }
        else if (val_1.is<long long>() && val_2.is<long double>()) {
            long double raw_res = val_1.as<long long>() * val_2.as<long double>();
            return Value(raw_res);
        }
        else if (val_1.is<long double>() && val_2.is<long long>()) {
            long double raw_res = val_1.as<long double>() * val_2.as<long long>();
            return Value(raw_res);
        }
        else if (val_1.is<long double>() && val_2.is<long double>()) {
            long double raw_res = val_1.as<long double>() * val_2.as<long double>();
            return Value(raw_res);
        }
        else if (val_1.is<std::string>() && val_2.is<long long>()) {
            std::string val_1_str = val_1.as<std::string>();
            std::string raw_res = "";
            for (long long i = 0;i<val_2.as<long long>();i++){
                raw_res = raw_res + val_1_str;
            }
            return Value(raw_res);
        }
        else if (val_1.is<long long>() && val_2.is<std::string>()) {
            std::string val_2_str = val_2.as<std::string>();
            std::string raw_res = "";
            for (long long i = 0;i<val_1.as<long long>();i++){
                raw_res = raw_res + raw_res;
            }
            return Value(raw_res);
        }
        else if (val_1.is<long long>() && val_2.is<std::vector<Value>>()){
            const std::vector<Value>& val_2_vec = val_2.as<std::vector<Value>>();
            std::vector<Value> raw_res;
            for (long long i = 0;i<val_1.as<long long>();i++){
                raw_res.insert(raw_res.end(), val_2_vec.begin(), val_2_vec.end());
            }
            return Value(raw_res);
        }
        else if (val_1.is<std::vector<Value>>() && val_2.is<long long>()){
            const std::vector<Value>& val_1_vec = val_1.as<std::vector<Value>>();
            std::vector<Value> raw_res;
            for (long long i = 0;i<val_2.as<long long>();i++){
                raw_res.insert(raw_res.end(), val_1_vec.begin(), val_1_vec.end());
            }
            return Value(raw_res);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'mul': " + get_dbg_type(val_1.value) + " * " + get_dbg_type(val_2.value), line, func);
            return Value(none{});
        }
    }
