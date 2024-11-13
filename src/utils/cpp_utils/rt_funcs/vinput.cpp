    static Value vinput(const Value& msg){
        std::cout << msg.tostr();
        std::string input;
        std::getline(std::cin, input);
        return Value(input);
    }
