template<typename T>
struct segtree{
    int n;
    vector<T> t;

    void build(vector<T> &v) {
        for (int i = n; i < 2 * n; i++) t[i] = v[i - n];
        for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, T value) {
        p += n;
        if (t[p] > value) return;
        for (t[p] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
    }

    T query(int l, int r) {
        T res = numeric_limits<T>::min();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, t[l++]);
            if (r&1) res = max(t[--r], res);
        }
        return res;
    }

    segtree(int n, T def = 0):n(n),t(n << 1, def) {}
};
