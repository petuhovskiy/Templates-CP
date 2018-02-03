template <typename T>
struct prefix {
    vector<T> p;

    T query(int r) {
        if (r < 0) return T();
        return p[r];
    }

    // query [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    prefix(const vector<T>& v): p(v.size()) {
        if (v.empty()) return;
        p[0] = v[0];
        for (int i = 1; i < v.size(); i++) {
            p[i] = p[i - 1] + v[i];
        }
    }
};
