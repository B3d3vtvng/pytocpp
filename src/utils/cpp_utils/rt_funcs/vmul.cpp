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
