    static Value vsub(const Value& val_1, const Value& val_2, const int line, const char* func){
        if (val_1.is<long long>() && val_2.is<long long>()) {
            long long raw_res = val_1.as<long long>() - val_2.as<long long>();
            return Value(raw_res);
        }
        else if (val_1.is<long long>() && val_2.is<long double>()) {
            long double raw_res = val_1.as<long long>() - val_2.as<long double>();
            return Value(raw_res);
        }
        else if (val_1.is<long double>() && val_2.is<long long>()) {
            long double raw_res = val_1.as<long double>() - val_2.as<long long>();
            return Value(raw_res);
        }
        else if (val_1.is<long double>() && val_2.is<long double>()) {
            long double raw_res = val_1.as<long double>() - val_2.as<long double>();
            return Value(raw_res);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'sub': " + get_dbg_type(val_1.value) + " - " + get_dbg_type(val_2.value), line, func);
            return Value(none{});
        }
    }
