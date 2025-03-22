    static Value vinput(const Value& msg, const int line, const char* func){
        std::cout << msg.tostr();
        std::string input;
        std::getline(std::cin, input);
        return Value(input);
    }
