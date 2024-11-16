    template<typename... Args>
    static Value vprint(const Args&... args) {
        ((std::cout << args.tostr() << " "), ...) << "\n";
        return Value(none{});
    }