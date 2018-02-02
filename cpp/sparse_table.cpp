template <typename T = int, const T& (*MX)(const T&, const T&) = std::max>
struct sparse_table{
    size_t n;
    vector<vector<T>> t;

    // query [l, r)
    T query(int l, int r) {
        int sz = r - l;
        int b = 31 - __builtin_clz(sz);
        return MX(t[l][b], t[r - (1 << b)][b]);
    }

    sparse_table(const vector<T> &v): n(v.size()), t(v.size()) {
        for (int i = 0; i < n; ++i) {
            t[i].push_back(v[i]);
        }
        for (int e = 1; (1 << e) <= n; ++e) {
            int sz = 1 << e;
            int half = sz >> 1;
            for (int i = 0; i + sz <= n; ++i) {
                t[i].push_back(MX(t[i][e - 1], t[i + half][e - 1]));
            }
        }
    }
};
