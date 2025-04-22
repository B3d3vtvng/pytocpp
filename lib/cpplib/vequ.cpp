    static Value vequ(const Value& val_1, const Value& val_2, const int line, const char* func, const char* invalid_v_name){
        return Value(val_1.equ(val_2, line, func, invalid_v_name));
    }
