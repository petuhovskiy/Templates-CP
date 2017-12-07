template <typename T>
struct MaxStack {
    vector<pair<T, T>> v;

    void push(T t) {
        if (v.empty()) {
            v.emplace_back(t, t);
        } else {
            v.emplace_back(t, std::max(t, max()));
        }
    }

    pair<T, T> back() const {
        return v.back();
    }

    T max() const {
        return v.back().second;
    }

    T pop() {
        auto tmp = v.back().first;
        v.pop_back();
        return tmp;
    }

    bool empty() const {
        return v.empty();
    }

    size_t size() const {
        return v.size();
    }
};

template <typename T>
struct MaxQueue {
    MaxStack<T> a, b;

    T max() const {
        if (a.empty()) {
            return b.max();
        } else if (b.empty()) {
            return a.max();
        } else {
            return std::max(a.max(), b.max());
        }
    }

    void push(T t) {
        a.push(t);
    }

    void transfer() {
        while (!a.empty()) {
            b.push(a.pop());
        }
    }

    T pop() {
        if (b.empty()) {
            transfer();
        }
        return b.pop();
    }

    bool empty() const {
        return a.empty() && b.empty();
    }

    size_t size() const {
        return a.size() + b.size();
    }
};
