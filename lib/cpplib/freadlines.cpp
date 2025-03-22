    static Value freadlines(const Value& fname_v, const int line, const char* func){
        value_t fname = fname_v.get_value();
        if (!std::holds_alternative<std::string>(fname)){
            RunTime instance;
            instance.throw_rt_error("Invalid filename", line, func);
            return Value(none{});
        }
        std::string fname_str = std::get<std::string>(fname);
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
        std::vector<Value> fcontent_vec;
        std::string cur_line;
        while (std::getline(file, cur_line)) { // Read each line from the file
            fcontent_vec.push_back(Value(cur_line));
        }

        file.close();

        return Value(fcontent_vec);
    }