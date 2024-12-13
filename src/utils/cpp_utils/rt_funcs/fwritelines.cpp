    static Value fwritelines(const Value fname_v, const Value finput_v){
        value_t fname = fname_v.get_value();
        value_t finput = finput_v.get_value();
        if (!std::holds_alternative<std::string>(fname) or !std::holds_alternative<std::vector<Value> >(finput)){
            RunTime instance;
            instance.throw_rt_error("Invalid filename");
            return Value(none{});
        }
        std::vector<Value> finput_vec = std::get<std::vector<Value> >(finput);
        std::string fname_str = std::get<std::string>(fname);
        std::ofstream file;
        try{
            file = std::ofstream(fname_str);
        }
        catch (...){
            RunTime instance;
            instance.throw_rt_error("Could not create a new file");
            return Value(none{});
        }
        if (!file) { // Check if the file was created successfully
            RunTime instance;
            instance.throw_rt_error("Could not create a new file");
            return Value(none{});
        }
        for (const auto line_v : finput_vec){
            std::string line = line_v.tostr();
            file << line << "\n";
        }
        file.close();
        return Value(none{});
    }