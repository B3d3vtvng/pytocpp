    static Value sleep(const Value& time_v, const int line, const char* func){
        value_t time = time_v.get_value();
        if (std::holds_alternative<long long>(time)){
            std::chrono::seconds time_sec = std::chrono::seconds(std::get<long long>(time));
            std::this_thread::sleep_for(time_sec);
        }
        else if (std::holds_alternative<long double>(time)){
            std::chrono::duration<long double> time_dur = std::chrono::duration<long double>(std::get<long double>(time));
            std::this_thread::sleep_for(time_dur);
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Invalid Argument type for built-in function sleep(): " + get_dbg_type(time) + ", should be: 'int' or 'float'", line, func);
        }
        return Value(none{});
    }