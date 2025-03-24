    static Value fcreate(const Value& fname_v, const int line, const char* func){
        value_t fname = fname_v.get_value();
        if (!std::holds_alternative<std::string>(fname)){
            RunTime instance;
            instance.throw_rt_error("Invalidtype for filename: " + get_dbg_type(fname) + ", should be: 'str'", line);
            return Value(none{});
        }
        std::string fname_str = std::get<std::string>(fname);
        std::ofstream file;
        try{
            file = std::ofstream(fname_str);
        }
        catch (...){
            RunTime instance;
            instance.throw_rt_error("Could not create a new file", line, func);
            return Value(none{});
        }
        if (!file) { // Check if the file was created successfully
            RunTime instance;
            instance.throw_rt_error("Could not create a new file", line, func);
            return Value(none{});
        }

        file.close();
        return Value(none{});
    }