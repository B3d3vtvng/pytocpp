    std::string tostr() const{
    return std::visit([](const auto &val) -> std::string
                      {
        std::ostringstream oss;
        using T = std::decay_t<decltype(val)>;

        if constexpr (std::is_same_v<T, std::vector<Value> >) {
            oss << "[";
            for (size_t i = 0; i < val.size(); i++) {
                if (val[i].template is<std::string>()) {
                    oss << "\"" + val[i].tostr() + "\"";
                } else {
                    oss << val[i].tostr();
                }
                
                if (i != val.size() - 1) {
                    oss << ", ";
                }
            }
            oss << "]";
        } else if constexpr (std::is_same_v<T, bool>) {
            oss << (val ? "True" : "False");
        } else if constexpr (std::is_same_v<T, std::string>) {
            oss << val;
        } else if constexpr (std::is_same_v<T, none>) {
            oss << "None";
        } else if constexpr (std::is_same_v<T, invalid>){
            //Do nothing to trick the compiler lmao
        } else {
            oss << val;
        }

        return oss.str(); }, value);
    }