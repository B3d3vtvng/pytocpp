//##########################################Header########################################################

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

class Value;

using none = std::monostate;
using value_t = std::variant<long long, long double, bool, std::string, std::vector<Value>, none>;

enum Compare{
    GREATER,
    LESS,
    GEQU,
    LEQU
};

using cmp_t  = Compare;

class Value {
private:
    value_t value;

public:
    Value(value_t new_value){
        value = new_value;
    }

    value_t get_value() const {
        return value;
    }
    bool operator==(const Value& val_1_v) const{
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = value;

        if (std::holds_alternative<long long>(val_1) && std::holds_alternative<long double>(val_2)) {
            return std::get<long long>(val_1) == std::get<long double>(val_2);
        }
        else if (std::holds_alternative<long double>(val_1) && std::holds_alternative<long long>(val_2)) {
            return std::get<long double>(val_1) == std::get<long long>(val_2);
        }

        if (val_1.index() != val_2.index()){
            return false;
        }

        if (std::holds_alternative<long long>(val_1)){
            return std::get<long long>(val_1) == std::get<long long>(val_2);
        }
        else if (std::holds_alternative<long double>(val_1)){
            return std::get<long double>(val_1) == std::get<long double>(val_2);
        }
        else if (std::holds_alternative<bool>(val_1)){
            return std::get<bool>(val_1) == std::get<bool>(val_2);
        }
        else if (std::holds_alternative<std::string>(val_1)){
            return std::get<std::string>(val_1) == std::get<std::string>(val_2);
        }
        else if (std::holds_alternative<std::vector<Value> >(val_1)){
            return std::get<std::vector<Value> >(val_1) == std::get<std::vector<Value> >(val_2);
        }
        else if (std::holds_alternative<none>(val_1)){
            return std::get<none>(val_1) == std::get<none>(val_2);
        }
        return false;
    }

    std::string tostr() const {
    return std::visit([](const auto& val) -> std::string {
        std::ostringstream oss;
        using T = std::decay_t<decltype(val)>;

        if constexpr (std::is_same_v<T, std::vector<Value> >) {
            oss << "[";
            for (size_t i = 0; i < val.size(); i++) {
                if (std::holds_alternative<std::string>(val[i].get_value())) {
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
        } else {
            oss << val;
        }

        return oss.str();
    }, value);
}


};


class RunTime {
private:
    void throw_rt_error(const std::string& error_msg) const{
        std::cout << "\n" << __FILE__ << ": RuntimeError: " << error_msg << "\n\n" << "NOTE: Please note that this tool only supports a subset of the python language - Please visit https://github.com/B3d3vtvng/pytocpp/blob/main/README.md#features for more information.\n\n";
        exit(1);
    }
public:
    static Value vadd(const Value& val_1_v, const Value& val_2_v) {
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
            instance.throw_rt_error("Invalid type for operation: 'add'");
            return Value(none{});
        }
    }

    static std::vector<Value> validate_iter(const Value iter_v){
        value_t iter = iter_v.get_value();

        if (std::holds_alternative<std::vector<Value> >(iter)){
            return std::get<std::vector<Value> >(iter);
        }
        else if (std::holds_alternative<std::string>(iter)){
            std::vector<Value> str_vec;
            for (const char chr : std::get<std::string>(iter)){
                str_vec.push_back(Value(std::string(1, chr)));
            }
            return str_vec;
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot iterate over value of non-container type");
            return std::vector<Value>{};
        }

    }

    static Value vequ(const Value& val_1_v, const Value& val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<long long>(val_1) && std::holds_alternative<long double>(val_2)) {
            return Value(std::get<long long>(val_1) == std::get<long double>(val_2));
        }
        else if (std::holds_alternative<long double>(val_1) && std::holds_alternative<long long>(val_2)) {
            return Value(std::get<long double>(val_1) == std::get<long long>(val_2));
        }

        if (val_1.index() != val_2.index()){
            return Value(false);
        }

        if (std::holds_alternative<long long>(val_1)){
            return Value(std::get<long long>(val_1) == std::get<long long>(val_2));
        }
        else if (std::holds_alternative<long double>(val_1)){
            return Value(std::get<long double>(val_1) == std::get<long double>(val_2));
        }
        else if (std::holds_alternative<bool>(val_1)){
            return Value(std::get<bool>(val_1) == std::get<bool>(val_2));
        }
        else if (std::holds_alternative<std::string>(val_1)){
            return Value(std::get<std::string>(val_1) == std::get<std::string>(val_2));
        }
        else if (std::holds_alternative<std::vector<Value> >(val_1)){
            return Value(std::get<std::vector<Value> >(val_1) == std::get<std::vector<Value> >(val_2));
        }
        else if (std::holds_alternative<none>(val_1)){
            return Value(std::get<none>(val_1) == std::get<none>(val_2));
        }
        return Value(false);
    }

    static Value vinput(const Value& msg){
        std::cout << msg.tostr();
        std::string input;
        std::getline(std::cin, input);
        return Value(input);
    }

    static Value vlen(const Value& container_v){
        value_t container = container_v.get_value();

        if (std::holds_alternative<std::vector<Value> >(container)){
            return Value(static_cast<long long>(std::get<std::vector<Value> >(container).size()));
        }
        else if (std::holds_alternative<std::string >(container)){
            return Value(static_cast<long long>(std::get<std::string>(container).length()));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot determine length of variable of a non-container type");
            return Value(none{});
        }
    }

    template<typename... Args>
    static Value vprint(const Args&... args) {
        ((std::cout << args.tostr() << " "), ...) << "\n";
        return Value(none{});
    }
    static bool vcondition(const Value& condition){
        if (!std::holds_alternative<bool>(condition.get_value())){
            RunTime instance;
            instance.throw_rt_error("Invalid type for conditional expression");
            return false;
        }

        return std::get<bool>(condition.get_value());
    }

};

//#############################################User Programm#################################################


Value reverse_string(Value string){
    if (RunTime::vcondition(RunTime::vequ(string, Value("")))){
        return Value("");
    }
    if (RunTime::vcondition(RunTime::vequ(RunTime::vlen(string), Value(1)))){
        return string;
    }
    Value new_string = Value("");
    for (Value _char : RunTime::validate_iter(string)){
        new_string = RunTime::vadd(_char, new_string);
    }
    return new_string;
}

int main(){
    while (RunTime::vcondition(Value(true))){
        Value user_input = RunTime::vinput(Value(">>> "));
        RunTime::vprint(reverse_string(user_input));
    }

    return 0;
}