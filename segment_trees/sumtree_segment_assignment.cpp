class segtree{
public:
    int n;  // array size
    vector<int> t;
    vector<int> d;
    int h;

    void build(vector<int> &v) {  // build the tree
        for (int i = n; i < 2 * n; i++) t[i] = v[i - n];
        for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }

    void calc(int p, int k) {
        if (d[p] == 0) t[p] = t[p<<1] + t[p<<1|1];
        else t[p] = d[p] * k;
    }

    void apply(int p, int value, int k) {
        t[p] = value * k;
        if (p < n) d[p] = value;
    }

	void resolve(int l, int r) {
        int k = 2;
        for (l += n, r += n-1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) calc(i, k);
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h-1);
        for (l += n, r += n-1; s > 0; --s, k >>= 1)
            for (int i = l >> s; i <= r >> s; ++i)
                if (d[i] != 0) {
                    apply(i<<1, d[i], k);
                    apply(i<<1|1, d[i], k);
                    d[i] = 0;
                }
    }

    void modify(int l, int r, int value) {
        if (value == 0) return;
        push(l, l + 1);
        push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l&1) apply(l++, value, k);
            if (r&1) apply(--r, value, k);
        }
        resolve(l0, l0 + 1);
        resolve(r0 - 1, r0);
    }

    int query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }

    segtree(int n):n(n),t(){
        h = 32 - __builtin_clz(n);
        t.resize(n << 1, 0);
        d.resize(n << 1, 0);
    }
};
