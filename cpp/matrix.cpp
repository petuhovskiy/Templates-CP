namespace matrix{

    template<typename T, size_t n, size_t m>
    using type = array<array<T, m>, n>;

    template<typename T, size_t n, size_t m>
    void print(type<T, n, m> &a, ostream &out = cout) {
        for (auto &i : a) {
            for (auto &j : i) out << j << " ";
            out << endl;
        }
    }

    template<typename T, size_t n, size_t m>
    void debug(const string &info, type<T, n, m> &a, ostream &out = cerr) {
        out << "#########" << info << "#########" << endl;
        print(a, out);
        out << "###END###" << info << "###END###" << endl;
    }

    template<typename T, size_t n, size_t m>
    inline type<T, n, m> createMatrix(T defaultValue = 0) {
        type<T, n, m> res;
        for (size_t i = 0; i < n; i++) res[i].fill(defaultValue);
        return res;
    }

    template<typename T, size_t n>
    inline type<T, n, n> createOneMatrix() {
        auto v = createMatrix<T, n, n>();
        for (size_t i = 0; i < n; i++) v[i][i] = 1;
        return v;
    }

    template<typename T, size_t l, size_t m, size_t n>
    inline type<T, l, n> mult(type<T, l, m> &a, type<T, m, n> &b) {
        auto res = createMatrix<T, l, n>();
        for (size_t i = 0; i < l; i++) {
            for (size_t j = 0; j < n; j++) {
                for (size_t z = 0; z < m; z++) {
                    res[i][j] += a[i][z] * b[z][j];
                }
            }
        }
        return res;
    }

    template<typename T, size_t n>
    inline type<T, n, n> binpow(type<T, n, n> &a, long long t) {
        auto res = createOneMatrix<T, n>();
        while (t) {
            if (t & 1) res = mult(res, a);
            a = mult(a, a);
            t >>= 1;
        }
        return res;
    }
};
