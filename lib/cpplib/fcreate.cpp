    static Value fcreate(const Value& fname, const int line, const char* func){
        if (!fname.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalidtype for filename: " + get_dbg_type(fname) + ", should be: 'str'", line);
            return Value(none{});
        }
        std::string fname_str = fname.as<std::string>();
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