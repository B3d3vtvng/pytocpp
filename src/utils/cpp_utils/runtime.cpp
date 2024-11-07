#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <sstream>

class Value;

using value_t = std::variant<int, float, bool, std::string, std::vector<Value> >;

class Value {
private:
    value_t value;

public:
    Value(value_t new_value){
        value = new_value;
    }

    std::string tostr() const {
        return std::visit([](const auto& val) -> std::string {
            std::ostringstream oss;
            using T = std::decay_t<decltype(val)>;
            
            if constexpr (std::is_same_v<T, std::vector<Value> >) {
                oss << "[";
                for (size_t i = 0; i < val.size(); i++) {
                    oss << val[i].tostr();
                    if (i != val.size() - 1) {
                        oss << ", ";
                    }
                }
                oss << "]";
            }
            else if constexpr (std::is_same_v<T, bool>){
                oss << (val ? "True" : "False");
            }
            else if constexpr (std::is_same_v<T, std::string>){
                oss << "\"" + val + "\"";
            }
            else {
                oss << val;
            }

            return oss.str();
        }, value);
    }

    value_t get_value() const {
        return value;
    }

    void set_value(const value_t new_value){
        value = new_value;
    }
};

enum Compare{
    GREATER,
    LESS,
    GEQU,
    LEQU
};

using cmp_t  = Compare;

class RunTime {
private:
    void throw_rt_error(const std::string& error_msg) const {
        std::cout << __FILE__ << ": RuntimeError: " << error_msg << "\n";
        exit(1);
    }

public:
    static Value vadd(const Value val_1_v, const Value val_2_v) {
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<int>(val_2)) {
            int raw_res = std::get<int>(val_1) + std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<int>(val_1) + std::get<float>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            float raw_res = std::get<float>(val_1) + std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<float>(val_1) + std::get<float>(val_2);
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
            return Value(1);
        }
    }

    static Value vsub(const Value val_1_v, const Value val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<int>(val_2)) {
            int raw_res = std::get<int>(val_1) - std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<int>(val_1) - std::get<float>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            float raw_res = std::get<float>(val_1) - std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<float>(val_1) - std::get<float>(val_2);
            return Value(raw_res);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'sub'");
            return Value(1);
        }
    }

    static Value vmul(const Value val_1_v, const Value val_2_v) {
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<int>(val_2)) {
            int raw_res = std::get<int>(val_1) * std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<int>(val_1) * std::get<float>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            float raw_res = std::get<float>(val_1) * std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<float>(val_1) * std::get<float>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<std::string>(val_1) && std::holds_alternative<int>(val_2)) {
            std::string val_1_str = std::get<std::string>(val_1);
            std::string raw_res = "";
            for (int i = 0;i<std::get<int>(val_2);i++){
                raw_res = raw_res + raw_res;
            }
            return Value(raw_res);
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<std::string>(val_2)) {
            std::string val_2_str = std::get<std::string>(val_2);
            std::string raw_res = "";
            for (int i = 0;i<std::get<int>(val_1);i++){
                raw_res = raw_res + raw_res;
            }
            return Value(raw_res);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'mul'");
            return Value(1);
        }
    }

    static Value vdiv(const Value val_1_v, const Value val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<int>(val_2)) {
            int raw_res = std::get<int>(val_1) / std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<int>(val_1) / std::get<float>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            float raw_res = std::get<float>(val_1) / std::get<int>(val_2);
            return Value(raw_res);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<float>(val_2)) {
            float raw_res = std::get<float>(val_1) / std::get<float>(val_2);
            return Value(raw_res);
        }
        else {
            RunTime instance;
            instance.throw_rt_error("Invalid type for operation: 'mul'");
            return Value(1);
        }
    }

    static Value vindex(const Value iterable_v, const Value index_v){
        value_t iterable = iterable_v.get_value();
        value_t index = index_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iterable)){
            RunTime instance;
            instance.throw_rt_error("A non-iterator cannot be indexed");
            return Value(1);
        }
        else if (!std::holds_alternative<int>(index)){
            RunTime instance;
            instance.throw_rt_error("Indexing expressions must be of type 'int'");
            return Value(1);
        }
        else if (std::get<int>(index) < 0 || std::get<int>(index) >= std::get<std::vector<Value> >(iterable).size()){
            RunTime instance;
            instance.throw_rt_error("List index out of bounds");
        }
        return std::get<std::vector<Value> >(iterable)[std::get<int>(index)];
    }

    static Value vslice(const Value iterable_v, const Value slice_left_v, const Value slice_right_v){
        value_t iterable = iterable_v.get_value();
        value_t slice_left = slice_left_v.get_value();
        value_t slice_right = slice_right_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iterable)){
            RunTime instance;
            instance.throw_rt_error("A non-iterator cannot be indexed");
            return Value(1);
        }
        else if (!std::holds_alternative<int>(slice_left) || !std::holds_alternative<int>(slice_right)){
            RunTime instance;
            instance.throw_rt_error("Slice expressions must be of type 'int'");
            return Value(1);
        }
        else if (std::get<int>(slice_left) < 0 || std::get<int>(slice_left) >= std::get<std::vector<Value> >(iterable).size() || std::get<int>(slice_right) < 0 || std::get<int>(slice_right) >= std::get<std::vector<Value> >(iterable).size()){
            RunTime instance;
            instance.throw_rt_error("Slice index out of bounds");
        }

        std::vector<Value> new_iterable;
        for (int i = std::get<int>(slice_left);i<std::get<int>(slice_right);i++){
            new_iterable.push_back(std::get<std::vector<Value> >(iterable)[i]);
        }
        return Value(new_iterable);
    }

    static Value vcompare(const Value val_1_v, const Value val_2_v, const cmp_t compare_type){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<int>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<int>(val_1) > std::get<int>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<int>(val_1) < std::get<int>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<int>(val_1) >= std::get<int>(val_2));
            }
            else{
                return Value(std::get<int>(val_1) <= std::get<int>(val_2));
            }
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<int>(val_1) > std::get<float>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<int>(val_1) < std::get<float>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<int>(val_1) >= std::get<float>(val_2));
            }
            else{
                return Value(std::get<int>(val_1) <= std::get<float>(val_2));
            }
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<float>(val_1) > std::get<int>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<float>(val_1) < std::get<int>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<float>(val_1) >= std::get<int>(val_2));
            }
            else{
                return Value(std::get<float>(val_1) <= std::get<int>(val_2));
            }
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<float>(val_2)) {
            if (compare_type == GREATER){
                return Value(std::get<float>(val_1) > std::get<float>(val_2));
            }
            else if (compare_type == LESS){
                return Value(std::get<float>(val_1) < std::get<float>(val_2));
            }
            else if (compare_type == GEQU){
                return Value(std::get<float>(val_1) >= std::get<float>(val_2));
            }
            else{
                return Value(std::get<float>(val_1) <= std::get<float>(val_2));
            }
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Invalid type for comparison");
            return Value(1);
        }
    }

    static Value vand(const Value val_1_v, const Value val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (!std::holds_alternative<bool>(val_1) | !std::holds_alternative<bool>(val_2)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'");
            return Value(1);
        }

        return Value(std::get<bool>(val_1) && std::get<bool>(val_2));
    }

    static Value vor(const Value val_1_v, const Value val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (!std::holds_alternative<bool>(val_1) | !std::holds_alternative<bool>(val_2)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'");
            return Value(1);
        }

        return Value(std::get<bool>(val_1) || std::get<bool>(val_2));
    }
};