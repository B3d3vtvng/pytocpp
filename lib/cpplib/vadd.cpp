    static Value vadd(const Value& val_1, const Value& val_2, const int line, const char* func) {
        if (val_1.is<long long>() && val_2.is<long long>()) {
            long long raw_res = val_1.as<long long>() + val_2.as<long long>();
            return Value(raw_res);
        }
        else if (val_1.is<long long>() && val_2.is<long double>()) {
            long double raw_res = val_1.as<long long>() + val_2.as<long double>();
            return Value(raw_res);
        }
        else if (val_1.is<long double>() && val_2.is<long long>()) {
            long double raw_res = val_1.as<long double>() + val_2.as<long long>();
            return Value(raw_res);
        }
        else if (val_1.is<long double>() && val_2.is<long double>()) {
            long double raw_res = val_1.as<long double>() + val_2.as<long double>();
            return Value(raw_res);
        }
        else if (val_1.is<std::string>() && val_2.is<std::string>()) {
            std::string raw_res = val_1.as<std::string>() + val_2.as<std::string>();
            return Value(raw_res);
        }
        else if (val_1.is<std::vector<Value> >() && val_2.is<std::vector<Value> >()) {
            std::vector<Value> val_1_vec = val_1.as<std::vector<Value> >();
            std::vector<Value> val_2_vec = val_2.as<std::vector<Value> >();
            val_1_vec.insert(val_1_vec.end(), val_2_vec.begin(), val_2_vec.end());
            return Value(val_1_vec);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'add': " + get_dbg_type(val_1.value) + " + " + get_dbg_type(val_2.value), line, func);
            return Value(none{});
        }
    }
