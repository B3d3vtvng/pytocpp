    static Value sleep(const Value& time, const int line, const char* func){
        if (time.is<long long>()){
            std::chrono::seconds time_sec = std::chrono::seconds(time.as<long long>());
            std::this_thread::sleep_for(time_sec);
        }
        else if (time.is<long double>()){
            std::chrono::duration<long double> time_dur = std::chrono::duration<long double>(time.as<long double>());
            std::this_thread::sleep_for(time_dur);
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Invalid Argument type for built-in function sleep(): " + get_dbg_type(time.value) + ", should be: 'int' or 'float'", line, func);
        }
        return Value(none{});
    }