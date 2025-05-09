//########################################## Header ########################################################

#include <iostream>
#include <variant>
#include <string>
#include <vector>

#define __fname__ %

class Value;
struct invalid {
    bool operator==(const invalid&) const {return true;}
};

using none = std::monostate;
using invalid = struct invalid;
using value_t = std::variant<long long, long double, bool, std::string, std::vector<Value>, none, invalid>;

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
