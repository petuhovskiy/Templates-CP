struct e {
    int sz;
    long long ans;

    void apply(long long x) {
        ans += x * sz;
    }

    e combine(e l, e r) {
        if (l.sz == 0) return r;
        if (r.sz == 0) return l;
        e res;
        res.sz = l.sz + r.sz;
        res.ans = l.ans + r.ans;
        return res;
    }

    e operator+(e r) {
        return combine(*this, r);
    }

    e(): sz(0), ans(0) {}
};

class segtree{

public:
    int n;  // array size
    vector<e> t;
    vector<long long> d;
    int h;

    void build() {  // build the tree
        for (int i = n; i < 2 * n; i++) {
            t[i] = e();
            t[i].sz = 1;
        }
        for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void apply(int p, int value) {
        t[p].apply(value);
        if (p < n) d[p] += value;
    }

    void calc(int p) {
        t[p] = t[p<<1] + t[p<<1|1];
        t[p].apply(d[p]);
    }

    void resolve(int v) {
        for (v += n; v > 1; ) calc(v >>= 1);
    }

    void push(int v) {
        v += n;
        for (int s = h; s > 0; s--) {
            int i = v >> s;
            if (d[i] != 0) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = 0;
            }
        }
    }

    void modify(int l, int r, int value) {
        push(l);
        push(r - 1);
        int l0 = l, r0 = r;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, value);
            if (r&1) apply(--r, value);
        }
        resolve(l0);
        resolve(r0 - 1);
    }

    e query(int l, int r) {  // sum on interval [l, r)
        push(l);
        push(r - 1);
        e ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = ansl + t[l++];
            if (r&1) ansr = t[--r] + ansr;
        }
        return ansl + ansr;
    }

    segtree(int n):n(n),t(){
        h = 32 - __builtin_clz(n);
        t.resize(n << 1);
        d.assign(n, 0);
    }
};
