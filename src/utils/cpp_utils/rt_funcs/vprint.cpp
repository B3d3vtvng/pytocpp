    template<typename... Args>
    static void vprint(const Args&... args) {
        ((std::cout << args.tostr() << " "), ...) << "\n";
    }