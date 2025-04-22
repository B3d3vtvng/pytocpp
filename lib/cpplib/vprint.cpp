    template<typename... Args>
    static Value vprint(const int line, const char* func, const char* invalid_v_name, const Args&... args) {
        ((std::cout << args.tostr(line, func, invalid_v_name) << " "), ...) << "\n";
        return Value(none{});
    }