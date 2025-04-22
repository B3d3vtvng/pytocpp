static Value vindex_assign(Value container, const Value& assign, const std::vector<Value>& idxs, const int line, const char* func) {
    if (!idxs[0].is<long long>()) {
        RunTime runtime;
        runtime.throw_rt_error("Indexing expressions must be of type int, not " + get_dbg_type(idxs[0].value), line, func);
        return Value(none{});
    }

    size_t current_idx = 0;
    long long idx = idxs[current_idx].as<long long>();

    if (container.is<std::vector<Value>>()) {
        auto& container_vec = container.as<std::vector<Value>>();
        if (idx >= container_vec.size()) {
            RunTime runtime;
            runtime.throw_rt_error("List index out of range", line, func);
            return Value(none{});
        }

        if (idxs.size() == 1) {
            container_vec[idx] = assign;
            return Value(std::move(container_vec));
        }

        Value new_vec = vindex_assign(container_vec[idx], assign, {idxs.begin() + 1, idxs.end()}, line, func);
        container_vec[idx] = std::move(new_vec);
        return Value(container_vec);
    }

    else if (container.is<std::string>()) {
        if (!assign.is<std::string>() || assign.as<std::string>().length() != 1) {
            RunTime runtime;
            runtime.throw_rt_error("Cannot assign non-character to index of string object", line, func);
            return Value(none{});
        }

        auto& container_str = container.as<std::string>();
        if (idx >= container_str.length()) {
            RunTime runtime;
            runtime.throw_rt_error("Assignment index out of range", line, func);
            return Value(none{});
        }

        container_str[idx] = assign.as<std::string>()[0];
        return Value(std::move(container_str));
    }

    RunTime runtime;
    runtime.throw_rt_error("Cannot assign value to index of non-container type: " + get_dbg_type(container.value), line, func);
    return Value(none{});
}