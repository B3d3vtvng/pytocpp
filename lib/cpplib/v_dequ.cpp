    bool equ(const Value& other, const int line, const char* func, const char* invalid_v_name) const{
        if (is<invalid>() && other.is<invalid>()){
            Runtime instance;
            throw_rt_error("RunTime Error: Undefined Variable '" + std::string(invalid_v_name) + "'");
            return false;
        }
        if (is<none>() && other.is<none>()){
            return true;
        }

        if (is<std::vector<Value>>() && other.is<std::vector<Value>>()){
            const std::vector<Value>& lvec = as<std::vector<Value>>();
            const std::vector<Value>& rvec = other.as<std::vector<Value>>();
            if (lvec.size() != rvec.size()){return false;}

            for (int i = 0; i < lvec.size(); i++){
                if (!(lvec[i] == rvec[i])){return false;}
            }
            return true;
        }

        if (is<long long>() && other.is<long double>()) {
            return static_cast<long double>(as<long long>()) == other.as<long double>();
        }

        if (is<long double>() && other.is<long long>()) {
            return as<long double>() == static_cast<long double>(other.as<long long>());
        }

        if (value.index() == other.value.index()){
            return value == other.value;
        }

        return false;
    }
