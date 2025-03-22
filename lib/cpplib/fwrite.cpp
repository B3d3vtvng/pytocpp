    static Value fwrite(const Value& fname_v, const Value finput_v, const int line, const char* func){
        value_t fname = fname_v.get_value();
        value_t finput = finput_v.get_value();
        if (!std::holds_alternative<std::string>(fname) or !std::holds_alternative<std::string>(finput)){
            RunTime instance;
            instance.throw_rt_error("Invalid filename", line, func);
            return Value(none{});
        }
        std::string finput_str = std::get<std::string>(finput);
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
        file << finput_str;
        file.close();
        return Value(none{});
    }