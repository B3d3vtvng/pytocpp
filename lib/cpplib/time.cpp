    static Value time(const int line, const char* func){
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return Value(std::chrono::duration<long double>(duration).count());
    }