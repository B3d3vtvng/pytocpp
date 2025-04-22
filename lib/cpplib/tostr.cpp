    static Value tostr(const Value& val, const int line, const char* func, const char* invalid_v_name){
        return Value(val.tostr(line, func, invalid_v_name));
    }
