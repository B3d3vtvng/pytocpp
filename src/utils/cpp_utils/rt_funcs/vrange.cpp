    template<typename... Args>
    static Value vrange(const Args&... args){
        std::vector<Value> arg_vec = { Value(args)... };

        long long start;
        long long stop;
        long long step;

        if (arg_vec.size() == 1){
            value_t stop_v = arg_vec[0].get_value();
            if (!std::holds_alternative<long long>(stop_v)){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function 'range'");
                return Value(none{});
            }

            start = 0;
            stop = std::get<long long>(stop_v);
            step = 1;
        }

        if (arg_vec.size() == 3){
            value_t step_v = arg_vec[2].get_value();
            if (!std::holds_alternative<long long>(step_v)){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function 'range'");
                return Value(none{});
            }
            step = std::get<long long>(step_v);
        }
        else{
            step = 1;
        }

        if (arg_vec.size() >= 2){
            value_t stop_v = arg_vec[1].get_value();
            value_t start_v = arg_vec[0].get_value();
            if (!std::holds_alternative<long long>(stop_v) || !std::holds_alternative<long long>(start_v)){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function 'range'");
                return Value(none{});
            }
            stop = std::get<long long>(stop_v);
            start = std::get<long long>(start_v);
        }

        std::vector<Value> output_vec;

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
            instance.throw_rt_error("range() arg3 must not be zero");
            return Value(none{});
        }

        return Value(output_vec);
    }
