    static Value vnequ(const Value& val_1, const Value& val_2, const int line, const char* func){
        return Value(!val_1 == val_2);
    }
