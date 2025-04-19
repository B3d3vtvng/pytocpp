    template<typename... Args>
    static Value vrange(const int line, const char* func, const Args&... args){
        const std::vector<Value>& arg_vec = { Value(args)... };

        long long start;
        long long stop;
        long long step;

        if (arg_vec.size() == 0 || arg_vec.size() > 3){
            RunTime instance;
            instance.throw_rt_error("Invalid argument count for function'range', expected: 1-3", line, func);
            return Value(none{});
        }

        for (const Value arg : arg_vec){
            if (!arg.is<long long>()){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function'range', expected: int, recieved: " + get_dbg_type(arg.value), line, func);
                return Value(none{});
            }
        }

        if (arg_vec.size() == 1){
            start = 0;
            stop = arg_vec[0].as<long long>();
            step = 1;
        }
        else if (arg_vec.size() == 2){
            start = arg_vec[0].as<long long>();
            stop = arg_vec[1].as<long long>();
            step = 1;
        }
        else{
            start = arg_vec[0].as<long long>();
            stop = arg_vec[1].as<long long>();
            step = arg_vec[2].as<long long>();
        }

        std::vector<Value> output_vec = std::vector<Value>();

        if (step > 0){
            for (long long i = start; i<stop;i+=step){
                output_vec.push_back(Value(i));
            }
        }
        else if (step < 0){
            for (long long i = start; i>stop;i+=step){
                output_vec.push_back(Value(i));
            }
        }
        else{
            RunTime instance;
            instance.throw_rt_error("range() arg3 must not be zero", line, func);
            return Value(none{});
        }

        return Value(output_vec);
    }
