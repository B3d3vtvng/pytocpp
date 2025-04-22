    std::string Value::tostr(const int line, const char* func, const char* invalid_v_name) const{
    if (is<invalid>()){
        RunTime instance;
        instance.throw_rt_error("RunTime Error: Undefined Variable: '" + std::string(invalid_v_name) + "'", line, func);
        return std::string();
    }
    return std::visit([line, func, invalid_v_name](const auto &val) -> std::string
                      {
        std::ostringstream oss;
        using T = std::decay_t<decltype(val)>;

        if constexpr (std::is_same_v<T, std::vector<Value> >) {
            oss << "[";
            for (size_t i = 0; i < val.size(); i++) {
                if (val[i].template is<std::string>()) {
                    oss << "\"" + val[i].tostr(line, func, invalid_v_name) + "\"";
                } else {
                    oss << val[i].tostr(line, func, invalid_v_name);
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
        } else {
            oss << val;
        }

        return oss.str(); }, value);
    }