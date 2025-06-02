template<typename... Args>
static Value vrange(const int line, const char* func, const Args&... args) {
    std::initializer_list<Value> arg_list = { Value(args)... };
    size_t argc = arg_list.size();

    long long raw[3] = {0, 0, 1};
    size_t i = 0;
    for (const Value& arg : arg_list) {
        if (!arg.is<long long>()) {
            RunTime instance;
            instance.throw_rt_error("Invalid argument type for function 'range', expected: int, received: " + get_dbg_type(arg.value), line, func);
            return Value(none{});
        }
        raw[i++] = arg.as<long long>();
    }

    long long start = (argc == 1) ? 0 : raw[0];
    long long stop  = (argc == 1) ? raw[0] : raw[1];
    long long step  = (argc == 3) ? raw[2] : 1;

    if (__builtin_expect((step == 0), 0)){
        RunTime instance;
        instance.throw_rt_error("range() arg3 must not be zero", line, func);
        return Value(none{});
    }

    size_t estimated_size = (step > 0)
        ? ((stop > start) ? static_cast<size_t>((stop - start + step - 1) / step) : 0)
        : ((start > stop) ? static_cast<size_t>((start - stop - step - 1) / -step) : 0);

    std::vector<Value> output_vec;
    output_vec.reserve(estimated_size);

    for (long long i = start;
         (step > 0) ? (i < stop) : (i > stop);
         i += step) {
        output_vec.emplace_back(i);
    }

    return Value(std::move(output_vec));
}
