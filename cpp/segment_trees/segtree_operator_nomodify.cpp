struct e {
    int sz;
    int pos;
    int mn;

    e combine(e l, e r) {
        if (l.sz == 0) return r;
        if (r.sz == 0) return l;
        e res;
        res.sz = l.sz + r.sz;
        if (l.mn < r.mn) {
            res.pos = l.pos;
            res.mn = l.mn;
        } else {
            res.pos = r.pos;
            res.mn = r.mn;
        }
        return res;
    }

    e operator+(e r) {
        return combine(*this, r);
    }

    e(): sz(0), ans(0) {}
    e(int x, int y): sz(1), pos(y), mn(x) {}
};

class segtree{

public:
    int n;  // array size
    vector<e> t;

    void build(vector<int> &v) {  // build the tree
        for (int i = n; i < 2 * n; i++) {
            t[i] = e(v[i - n], i - n);
        }
        for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    e query(int l, int r) {  // sum on interval [l, r)
        e ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = ansl + t[l++];
            if (r&1) ansr = t[--r] + ansr;
        }
        return ansl + ansr;
    }

    segtree(int n):n(n),t(){
        t.resize(n << 1);
    }
};
