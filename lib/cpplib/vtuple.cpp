class Tuple {
private:
    std::unique_ptr<Value[]> data;
    std::size_t size;

public:
    template<typename... Args>
    Tuple(Args... args) : size(sizeof...(args)), data(std::make_unique<Value[]>(sizeof...(args))) {
        std::initializer_list<Value> arg_list = { Value(args)... };
        std::size_t i = 0;
        for (const Value& arg : arg_list) {
            data[i++] = arg;
        }
    }

    Tuple(const Tuple& tup1, const Tuple& tup2) : size(tup1.get_size() + tup2.get_size()), data(std::make_unique<Value[]>(tup1.get_size() + tup2.get_size())) {
        std::size_t i = 0;
        for (std::size_t j = 0; j < tup1.get_size(); ++j) {
            data[i++] = tup1[j];
        }
        for (std::size_t j = 0; j < tup2.get_size(); ++j) {
            data[i++] = tup2[j];
        }
    }

    Tuple(const Tuple& other) : size(other.get_size()), data(std::make_unique<Value[]>(other.get_size())) {
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    std::size_t get_size() const {
        return size;
    }

    std::unique_ptr<Value[]> get_data(std::size_t index) {
        return data;
    }
}