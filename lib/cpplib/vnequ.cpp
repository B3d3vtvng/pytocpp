    static Value vnequ(const Value& val_1_v, const Value& val_2_v, const int line, const char* func){
        return Value(!std::get<bool>(RunTime::vequ(val_1_v, val_2_v).get_value()));
    }
