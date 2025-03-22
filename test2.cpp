//########################################## Header ########################################################

#include <iostream>
#include <variant>
#include <string>
#include <vector>

#define __fname__ "test2.py"

class Value;

using none = std::monostate;
using value_t = std::variant<long long, long double, bool, std::string, std::vector<Value>, none>;

enum Compare {
    GREATER,
    LESS,
    GEQU,
    LEQU
};

using cmp_t = Compare;

class Value {
private:
    value_t value;

public:
    Value() {
        value = none{};
    }
    Value(value_t new_value) {
        value = new_value;
    }

    value_t get_value() const {
        return value;
    }
};

class RunTime {
private:
    void throw_rt_error(const std::string& error_msg, const int line, const char* func) const {
        std::cout << "\n"
                  << __fname__ << ":" << line << " in " << func << "(): " << "RuntimeError: " << error_msg
                  << "\n\nNOTE: Please note that this tool only supports a subset of the Python language."
                  << " - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n\n";
        exit(1);
    }
public:
    static Value vadd(const Value& val_1_v, const Value& val_2_v, const int line, const char* func) {
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<long long>(val_1) && std::holds_alternative<long long>(val_2)) {
            long long raw_res = std::get<long long>(val_1) + std::get<long long>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<long long>(val_1) && std::holds_alternative<long double>(val_2)) {
            long double raw_res = std::get<long long>(val_1) + std::get<long double>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<long double>(val_1) && std::holds_alternative<long long>(val_2)) {
            long double raw_res = std::get<long double>(val_1) + std::get<long long>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<long double>(val_1) && std::holds_alternative<long double>(val_2)) {
            long double raw_res = std::get<long double>(val_1) + std::get<long double>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<std::string>(val_1) && std::holds_alternative<std::string>(val_2)) {
            std::string raw_res = std::get<std::string>(val_1) + std::get<std::string>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<std::vector<Value> >(val_1) && std::holds_alternative<std::vector<Value> >(val_2)) {
            std::vector<Value> val_1_vec = std::get<std::vector<Value> >(val_1);
            std::vector<Value> val_2_vec = std::get<std::vector<Value> >(val_2);
            val_1_vec.insert(val_1_vec.end(), val_2_vec.begin(), val_2_vec.end());
            return Value(val_1_vec);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'add'", line, func);
            return Value(none{});
        }
    }

static Value vindex(const Value& container_v, std::vector<Value> idxs_v, const int line, const char* func){
        value_t container = container_v.get_value();
        if (!std::holds_alternative<long long>(idxs_v[0].get_value())){
            RunTime runtime;
            runtime.throw_rt_error("Indexing expressions must be of type int!", line, func);
            return Value(none{});
        }
        long long idx = std::get<long long>(idxs_v[0].get_value());
        if (std::holds_alternative<std::vector<Value>  >(container)){
            std::vector<Value> container_vec = std::get<std::vector<Value> >(container);
            if (idx > container_vec.size()-1){
                RunTime runtime;
                runtime.throw_rt_error("List index out of range", line, func);
                return Value(none{});
            }
            if (idxs_v.size() == 1){
                return container_vec[idx];
            }
            idxs_v.erase(idxs_v.begin());
            return vindex(container_vec[idx], idxs_v, line, func);
        }
        else if (std::holds_alternative<std::string>(container_v.get_value())){
            std::string container_str = std::get<std::string>(container_v.get_value());
            if (idx > container_str.length()-1){
                RunTime runtime;
                runtime.throw_rt_error("Indexing expressions must be of type int!", line, func);
                return Value(none{});
            }
            if (idxs_v.size() == 1){
                return Value(std::string(1, container_str[idx]));
            }
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type", line, func);
            return Value(none{});
        }
        else{
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign value to index of non-container type", line, func);
            return Value(none{});
        }
    }
};

//############################################# User Program #################################################


Value argc;
Value argv;

Value test(Value x){
    Value var = RunTime::vindex(x, std::vector<Value>{Value(0)}, 2, "test");
    var = RunTime::vadd(var, Value(""), 3, "test");
    return Value(std::monostate{});
}

int main(int __argc, char** __argv){
    argc = Value(__argc);
    argv = Value([__argc, __argv]() {
        std::vector<Value> _argv;
        for (int i = 0; i < __argc; ++i) {
            _argv.emplace_back(Value(__argv[i]));
        }
        return _argv;
    }());

    test(Value(std::vector<Value>{Value(1)}));

    return 0;
}