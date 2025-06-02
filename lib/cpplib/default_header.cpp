//########################################## Header ########################################################

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

#define __fname__ %

class Value;

struct invalid {
    bool operator==(const invalid&) const {return true;}
};

using none = std::monostate;
using invalid = struct invalid;
using value_t = std::variant<long long, long double, bool, std::string, std::vector<Value>, std::unordered_map<Value, Value>, none, invalid>;

enum Compare {
    GREATER,
    LESS,
    GEQU,
    LEQU
};

using cmp_t = Compare;

class Value {
public:
    value_t value;

    Value() noexcept : value(invalid{}) {}

    Value(value_t new_value) noexcept : value(std::move(new_value)) {}

    template <typename T>
    T& as() {
        return std::get<T>(value);
    }

    template <typename T>
    const T& as() const {
        return std::get<T>(value);
    }

    template <typename T>
    bool is() const {
        return std::holds_alternative<T>(value);
    }
};

namespace std {
    template <>
    struct hash<Value> {
        size_t operator()(const Value& val) const noexcept {
            return std::visit([](const auto &v) -> size_t {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, std::string>) {
                    return std::hash<std::string>{}(v);
                } else if constexpr (std::is_same_v<T, long long>) {
                    return std::hash<long long>{}(v);
                } else if constexpr (std::is_same_v<T, long double>) {
                    return std::hash<long double>{}(v);
                } else if constexpr (std::is_same_v<T, bool>) {
                    return std::hash<bool>{}(v);
                } else if constexpr (std::is_same_v<T, none> || std::is_same_v<T, invalid>) {
                    return 0;
                } else if constexpr (std::is_same_v<T, std::unordered_map<Value, Value>>) {
                    size_t seed = 0;
                    for (const auto& [key, val] : v) {
                        size_t pair_hash = std::hash<Value>{}(key) ^ (std::hash<Value>{}(val) << 1);
                        seed ^= pair_hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    }
                    return seed;
                } else if constexpr (std::is_same_v<T, std::vector<Value>>) {
                    size_t seed = 0;
                    for (const auto& elem : v) {
                        seed ^= std::hash<Value>{}(elem) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    }
                    return seed;
                } else {
                    return 0;
                }
            }, val.value);
        }
    };
}


class RunTime {
private:
    static std::string get_dbg_type(value_t val){
        const std::string types[6] = {"'int'", "'float'", "'bool'", "'str'", "'list'", "'NoneType'"};
        return types[val.index()];
    }

    void throw_rt_error(const std::string& error_msg, const int line, const char* func) const {
        std::cout << "\n"
                  << __fname__ << ":" << line << " in " << func << "(): " << "RuntimeError: " << error_msg
                  << "\n\nNOTE: Please note that this tool only supports a subset of the Python language."
                  << " - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n\n";
        exit(1);
    }
};

//############################################# User Program #################################################
