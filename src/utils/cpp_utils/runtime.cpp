//##########################################Header########################################################

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <sstream>

class Value;

using none = std::monostate;
using value_t = std::variant<int, float, bool, std::string, std::vector<Value>, none>;

class Value {
private:
    value_t value;

public:
    Value(value_t new_value){
        value = new_value;
    }

    std::string tostr() const{
        return std::visit([](const auto& val) -> std::string {
            std::ostringstream oss;
            using T = std::decay_t<decltype(val)>;
            
            if constexpr (std::is_same_v<T, std::vector<Value> >){
                oss << "[";
                for (size_t i = 0; i < val.size(); i++) {
                    if (std::holds_alternative<std::string>(val[i].get_value())){
                        oss << "\"" + val[i].tostr() + "\"";
                    }
                    else{
                        oss << val[i].tostr();
                        if (i != val.size() - 1) {
                            oss << ", ";
                    }
                    }
                }
                oss << "]";
            }
            else if constexpr (std::is_same_v<T, bool>){
                oss << (val ? "True" : "False");
            }
            else if constexpr (std::is_same_v<T, std::string>){
                oss << val;
            }
            else if constexpr(std::is_same_v<T, none>){
                oss << "None";
            }
            else {
                oss << val;
            }

            return oss.str();
        }, value);
    }

    value_t get_value() const{
        return value;
    }

    bool operator==(const Value& val_1_v) const{
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = value;

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            return std::get<int>(val_1) == std::get<float>(val_2);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            return std::get<float>(val_1) == std::get<int>(val_2);
        }

        if (val_1.index() != val_2.index()){
            return false;
        }

        if (std::holds_alternative<int>(val_1)){
            return std::get<int>(val_1) == std::get<int>(val_2);
        }
        else if (std::holds_alternative<float>(val_1)){
            return std::get<float>(val_1) == std::get<float>(val_2);
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
    void throw_rt_error(const std::string& error_msg) const{
        std::cout << __FILE__ << ": RuntimeError: " << error_msg << "\n";
        exit(1);
    }

public:
    static Value vadd(const Value& val_1_v, const Value& val_2_v) {
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
            return Value(none{});
        }
    }

    static Value vsub(const Value& val_1_v, const Value& val_2_v){
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
            return Value(none{});
        }
    }

    static Value vmul(const Value& val_1_v, const Value& val_2_v) {
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
                raw_res = raw_res + val_1_str;
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
            return Value(none{});
        }
    }

    static Value vdiv(const Value& val_1_v, const Value& val_2_v){
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
            return Value(none{});
        }
    }

    static Value vindex(const Value& iterable_v, const Value& index_v){
        value_t iterable = iterable_v.get_value();
        value_t index = index_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iterable)){
            RunTime instance;
            instance.throw_rt_error("A non-iterator cannot be indexed");
            return Value(none{});
        }
        else if (!std::holds_alternative<int>(index)){
            RunTime instance;
            instance.throw_rt_error("Indexing expressions must be of type 'int'");
            return Value(none{});
        }
        else if (std::get<int>(index) < 0 || std::get<int>(index) >= std::get<std::vector<Value> >(iterable).size()){
            RunTime instance;
            instance.throw_rt_error("List index out of bounds");
            return Value(none{});
        }
        return std::get<std::vector<Value> >(iterable)[std::get<int>(index)];
    }

    static Value vslice(const Value& iterable_v, const Value& slice_left_v, const Value& slice_right_v){
        value_t iterable = iterable_v.get_value();
        value_t slice_left = slice_left_v.get_value();
        value_t slice_right = slice_right_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iterable)){
            RunTime instance;
            instance.throw_rt_error("A non-iterator cannot be indexed");
            return Value(none{});
        }
        else if (!std::holds_alternative<int>(slice_left) || !std::holds_alternative<int>(slice_right)){
            RunTime instance;
            instance.throw_rt_error("Slice expressions must be of type 'int'");
            return Value(none{});
        }
        else if (std::get<int>(slice_left) < 0 || std::get<int>(slice_left) > std::get<std::vector<Value> >(iterable).size() || std::get<int>(slice_right) < 0 || std::get<int>(slice_right) > std::get<std::vector<Value> >(iterable).size()){
            RunTime instance;
            instance.throw_rt_error("Slice index out of bounds");
            return Value(none{});

        }

        std::vector<Value> new_iterable;
        for (int i = std::get<int>(slice_left);i<std::get<int>(slice_right);i++){
            new_iterable.push_back(std::get<std::vector<Value> >(iterable)[i]);
        }
        return Value(new_iterable);
    }

    static bool vcompare(const Value& val_1_v, const Value& val_2_v, const cmp_t& compare_type){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<int>(val_2)) {
            if (compare_type == GREATER){
                return std::get<int>(val_1) > std::get<int>(val_2);
            }
            else if (compare_type == LESS){
                return std::get<int>(val_1) < std::get<int>(val_2);
            }
            else if (compare_type == GEQU){
                return std::get<int>(val_1) >= std::get<int>(val_2);
            }
            else{
                return std::get<int>(val_1) <= std::get<int>(val_2);
            }
        }
        else if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            if (compare_type == GREATER){
                return std::get<int>(val_1) > std::get<float>(val_2);
            }
            else if (compare_type == LESS){
                return std::get<int>(val_1) < std::get<float>(val_2);
            }
            else if (compare_type == GEQU){
                return std::get<int>(val_1) >= std::get<float>(val_2);
            }
            else{
                return std::get<int>(val_1) <= std::get<float>(val_2);
            }
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            if (compare_type == GREATER){
                return std::get<float>(val_1) > std::get<int>(val_2);
            }
            else if (compare_type == LESS){
                return std::get<float>(val_1) < std::get<int>(val_2);
            }
            else if (compare_type == GEQU){
                return std::get<float>(val_1) >= std::get<int>(val_2);
            }
            else{
                return std::get<float>(val_1) <= std::get<int>(val_2);
            }
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<float>(val_2)) {
            if (compare_type == GREATER){
                return std::get<float>(val_1) > std::get<float>(val_2);
            }
            else if (compare_type == LESS){
                return std::get<float>(val_1) < std::get<float>(val_2);
            }
            else if (compare_type == GEQU){
                return std::get<float>(val_1) >= std::get<float>(val_2);
            }
            else{
                return std::get<float>(val_1) <= std::get<float>(val_2);
            }
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Invalid type for comparison");
            return false;
        }
    }

    static bool vequ(const Value& val_1_v, const Value& val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (std::holds_alternative<int>(val_1) && std::holds_alternative<float>(val_2)) {
            return std::get<int>(val_1) == std::get<float>(val_2);
        }
        else if (std::holds_alternative<float>(val_1) && std::holds_alternative<int>(val_2)) {
            return std::get<float>(val_1) == std::get<int>(val_2);
        }

        if (val_1.index() != val_2.index()){
            return false;
        }

        if (std::holds_alternative<int>(val_1)){
            return std::get<int>(val_1) == std::get<int>(val_2);
        }
        else if (std::holds_alternative<float>(val_1)){
            return std::get<float>(val_1) == std::get<float>(val_2);
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

    static bool vnequ(const Value& val_1_v, const Value& val_2_v){
        return !RunTime::vequ(val_1_v, val_2_v);
    }

    static Value vand(const Value& val_1_v, const Value& val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (!std::holds_alternative<bool>(val_1) || !std::holds_alternative<bool>(val_2)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'");
            return Value(none{});
        }

        return Value(std::get<bool>(val_1) && std::get<bool>(val_2));
    }

    static Value vor(const Value& val_1_v, const Value& val_2_v){
        value_t val_1 = val_1_v.get_value();
        value_t val_2 = val_2_v.get_value();

        if (!std::holds_alternative<bool>(val_1) || !std::holds_alternative<bool>(val_2)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'");
            return Value(none{});
        }

        return Value(std::get<bool>(val_1) || std::get<bool>(val_2));
    }

    static Value vnot(const Value& val_v){
        value_t val = val_v.get_value();

        if (!std::holds_alternative<bool>(val)){
            RunTime instance;
            instance.throw_rt_error("Logical operations must be of type 'bool'");
            return Value(none{});
        }

        return Value(!std::get<bool>(val));
    }

    static Value vneg(const Value& val_v){
        value_t val = val_v.get_value();

        if (std::holds_alternative<int>(val)){
            return Value(-std::get<int>(val));
        }
        else if (std::holds_alternative<float>(val)){
            return Value(-std::get<float>(val));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot negate a value that is not of type 'int' or type 'float'");
            return Value(none{}); 
        }
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
            return Value(static_cast<int>(std::get<std::vector<Value> >(container).size()));
        }
        else if (std::holds_alternative<std::string >(container)){
            return Value(static_cast<int>(std::get<std::string>(container).length()));
        }
        else{
            RunTime instance;
            instance.throw_rt_error("Cannot determine length of variable of a non-container type");
            return Value(none{});
        }
    }

    static Value tostr(const Value& val){
        return Value(val.tostr());
    }

    template<typename... Args>
    static Value vrange(const Args&... args){
        std::vector<Value> arg_vec = { Value(args)... };

        int start;
        int stop;
        int step;

        if (arg_vec.size() == 1){
            value_t stop_v = arg_vec[0].get_value();
            if (!std::holds_alternative<int>(stop_v)){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function 'range'");
                return Value(none{});
            }

            start = 0;
            stop = std::get<int>(stop_v);
            step = 1;
        }

        if (arg_vec.size() == 3){
            value_t step_v = arg_vec[2].get_value();
            if (!std::holds_alternative<int>(step_v)){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function 'range'");
                return Value(none{});
            }
            step = std::get<int>(step_v);
        }
        else{
            step = 1;
        }

        if (arg_vec.size() >= 2){
            value_t stop_v = arg_vec[1].get_value();
            value_t start_v = arg_vec[0].get_value();
            if (!std::holds_alternative<int>(stop_v) || !std::holds_alternative<int>(start_v)){
                RunTime instance;
                instance.throw_rt_error("Invalid argument type for function 'range'");
                return Value(none{});
            }
            stop = std::get<int>(stop_v);
            start = std::get<int>(start_v);
        }

        std::vector<Value> output_vec;

        if (step > 0){
            for (int i = start; i<stop;i+=step){
                output_vec.push_back(Value(i));
            }
        }
        else if (step < 0){
            for (int i = start; i>stop;i+=step){
                output_vec.push_back(Value(i));
            }
        }
        else{
            RunTime instance;
            instance.throw_rt_error("range() arg3 must not be zero");
            return Value(none{});
        }

        return Value(output_vec);
    }

    static std::vector<Value> validate_iter(const Value iter_v){
        value_t iter = iter_v.get_value();

        if (!std::holds_alternative<std::vector<Value> >(iter)){
            RunTime instance;
            instance.throw_rt_error("Cannot iterate over value of non-container type");
            return std::vector<Value>{};
        }

        return std::get<std::vector<Value> >(iter);
    }

    template<typename... Args>
    static void vprint(const Args&... args) {
        ((std::cout << args.tostr() << " "), ...) << "\n";
    }
};

//#############################################User Programm#################################################