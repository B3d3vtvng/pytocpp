    static Value fread(const Value& fname_v){
        value_t fname = fname_v.get_value();
        if (!std::holds_alternative<std::string>(fname)){
            RunTime instance;
            instance.throw_rt_error("Invalid filename");
            return Value(none{});
        }
        std::string fname_str = std::get<std::string>(fname);
        std::ifstream file;
        try{
            file = std::ifstream(fname_str);
        }
        catch (...){
            RunTime instance;
            instance.throw_rt_error("File '" + fname_str + "' was not found");
            return Value(none{});
        }
        if (!file.is_open()){
            RunTime instance;
            instance.throw_rt_error("Could not open file");
            return Value(none{});
        }
        std::ostringstream fcontent;
        fcontent << file.rdbuf();
        std::string fcontent_str = fcontent.str();

        file.close();

        return Value(fcontent_str);
    }