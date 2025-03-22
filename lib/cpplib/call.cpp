    static void _call(){
        __in_func__ = true;
    }

    static void _call_exit(){
        __in_func__ = false;
        for (const std::string varname : __local_vars__){
            __dict__.erase(varname);
        }
    }

    template <typename T, typename... ArgTypes>
    static Value call(T func, ArgTypes... args){
        RunTime::_call();
        Value retval = func(std::forward<ArgTypes>(args)...);
        RunTime::_call_exit();
        return retval;
    }