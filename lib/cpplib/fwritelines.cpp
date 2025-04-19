    static Value fwritelines(const Value& fname, const Value& finput, const int line, const char* func){
        if (!fname.is<std::string>()){
            RunTime instance;
            instance.throw_rt_error("Invalid type for filename: " + get_dbg_type(fname.value), line, func);
            return Value(none{});
        }

        if (!finput.is<std::vector<Value>>()){
            RunTime instance;
            instance.throw_rt_error("Invalid type for file input: " + get_dbg_type(fname.value) + ", should be: 'list[str]'", line, func);
            return Value(none{});
        }

        std::vector<Value> finput_vec = finput.as<std::vector<Value>>();
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

        for (const Value line : finput_vec){
            if (!line.is<std::string>()){
                RunTime instance;
                instance.throw_rt_error("Invalid type for file input: " + get_dbg_type(line.value) + ", should be: 'list[str]'", line, func);
                return Value(none{});
            }

            file << line.as<std::string>() << "\n";
        }
        file.close();
        return Value(none{});
    }