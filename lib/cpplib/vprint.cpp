    template<typename... Args>
    static Value vprint(const int line, const char* func, const Args&... args) {
        ((std::cout << args.tostr() << " "), ...) << "\n";
        return Value(none{});
    }