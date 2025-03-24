    static Value fwritelines(const Value& fname_v, const Value& finput_v, const int line, const char* func){
        value_t fname = fname_v.get_value();
        value_t finput = finput_v.get_value();
        if (!std::holds_alternative<std::string>(fname)){
            RunTime instance;
            instance.throw_rt_error("Invalid type for filename: " + get_dbg_type(fname), line, func);
            return Value(none{});
        }

        if (!std::holds_alternative<std::vector<Value> >(finput)){
            RunTime instance;
            instance.throw_rt_error("Invalid type for file input: " + get_dbg_type(fname) + ", should be: 'list[str]'", line, func);
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
            instance.throw_rt_error("Could not create a new file", line, func);
            return Value(none{});
        }
        if (!file) { // Check if the file was created successfully
            RunTime instance;
            instance.throw_rt_error("Could not create a new file", line, func);
            return Value(none{});
        }

        value_t line;

        for (const auto line_v : finput_vec){
            line = line_v.get_value();

            if (!std::holds_alternative<std::string>(line)){
                RunTime instance;
                instance.throw_rt_error("Invalid type for file input: " + get_dbg_type(line) + ", should be: 'list[str]'", line, func);
                return Value(none{});
            }

            file << line << "\n";
        }
        file.close();
        return Value(none{});
    }