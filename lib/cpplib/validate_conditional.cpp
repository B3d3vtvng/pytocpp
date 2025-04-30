    template <typename... Conditionals>
    static void validate_conditional(const int line, const char* func, std::vector<const char*> names, Conditionals... conditionals){
        Value conditionals_array[] = {conditionals...};
        size_t conditional_count = sizeof...(conditionals);

        for (size_t i = 0; i < conditional_count; i++){
            if (conditionals_array[i].template is<invalid>()){
                RunTime instance;
                instance.throw_rt_error("RunTime Error: Undefined Identifier: " + std::string(names[i]), line, func);
            }
        }

        return;
    }