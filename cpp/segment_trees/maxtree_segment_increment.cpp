template<typename T>
struct segtree{
    int n;
    vector<T> t;
    vector<T> d;
    int h;

    void build(vector<T> &v) {
        for (int i = n; i < 2 * n; i++) t[i] = v[i - n];
        for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }

    void apply(int p, T value) {
        t[p] += value;
        if (p < n) d[p] += value;
    }

    void recalc(int p) {
        while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
    }

    void push(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = 0;
            }
        }
    }

    void inc(int l, int r, T value) {
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, value);
            if (r & 1) apply(--r, value);
        }
        recalc(l0);
        recalc(r0 - 1);
    }

    T query(int l, int r) {
        l += n, r += n;
        push(l);
        push(r - 1);
        T res = numeric_limits<T>::min();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(t[--r], res);
        }
        return res;
    }

    segtree(int n): n(n), t(n << 1, 0), h(32 - __builtin_clz(n)), d(n, 0) {}
};
