    static Value fread(const Value& fname, const int line, const char* func){
        if (!fname.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalid type for filename: " + get_dbg_type(fname) + ", should be: 'str'", line, func);
            return Value(none{});
        }
        std::string fname_str = fname.as<std::string>();
        std::ifstream file;
        try{
            file = std::ifstream(fname_str);
        }
        catch (...){
            RunTime instance;
            instance.throw_rt_error("File '" + fname_str + "' was not found", line, func);
            return Value(none{});
        }
        if (!file.is_open()){
            RunTime instance;
            instance.throw_rt_error("Could not open file", line, func);
            return Value(none{});
        }
        std::ostringstream fcontent;
        fcontent << file.rdbuf();
        std::string fcontent_str = fcontent.str();

        file.close();

        return Value(fcontent_str);
    }