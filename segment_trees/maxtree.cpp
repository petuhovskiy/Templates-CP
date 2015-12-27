class segtree{
public:
    int n;  // array size
    vector<int> t;

    void build(vector<int> &v) {  // build the tree
        for (int i = n; i < 2 * n; i++) t[i] = v[i - n];
        for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, int value) {  // set value at position p
        for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
    }

    int query(int l, int r) {  // sum on interval [l, r)
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, t[l++]);
            if (r&1) res = max(t[--r], res);
        }
        return res;
    }

    segtree(int n):n(n),t(){
        t.resize(n << 1, 0);
    }
};
