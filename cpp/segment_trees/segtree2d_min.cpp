class segtree{
public:
    int n;  // array size
    vector<int> t;

    void build(vector<int> &v) {  // build the tree
        for (int i = n; i < 2 * n; i++) t[i] = v[i - n];
        for (int i = n - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
    }

    void build(segtree &t1, segtree &t2) {  // build the tree
        for (int i = 1; i < 2 * n; i++) t[i] = min(t1.t[i], t2.t[i]);
    }

    int query(int l, int r) {  // sum on interval [l, r)
        int res = 2e9;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t[l++]);
            if (r&1) res = min(res, t[--r]);
        }
        return res;
    }

    segtree(int n):n(n),t(){
        t.resize(n << 1);
    }
};

class segtree2{
public:
    int n, m;  // array size
    vector<segtree> t;

    void build(vector<vector<int> > &v) {  // build the tree
        for (int i = 0; i < n; i++) {
            t[n + i].build(v[i]);
        }
        for (int i = n - 1; i > 0; i--) {
            t[i].build(t[i * 2], t[i * 2 + 1]);
        }
    }

    int query(int d, int l, int u, int r) {  // sum on interval [l, r)
        int res = 2e9;
        for (d += n, u += n; d < u; d >>= 1, u >>= 1) {
            if (d&1) res = min(res, t[d++].query(l, r));
            if (u&1) res = min(res, t[--u].query(l, r));
        }
        return res;
    }

    segtree2(int n, int m, vector<vector<int> > &v):n(n),m(m),t(){
        t.assign(n << 1, segtree(m));
        build(v);
    }
};
