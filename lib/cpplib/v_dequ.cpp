    bool operator==(const Value& other) const{
        if (is<none>() && other.is<none>()){
            return true;
        }

        if (is<std::vector<Value>>() && other.is<std::vector<Value>>()){
            const std::vector<Value>& lvec = as<std::vector<Value>>();
            const std::vector<Value>& rvec = other.as<std::vector<Value>>();
            if (lvec.size() != rvec.size()){return false;}

            for (int i = 0; i < lvec.size(), i++){
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
    }
