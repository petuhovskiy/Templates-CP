class segtree{
struct e {
	int a, b;
};

public:
    int n;  // array size
    vector<e> t;

	const e null_e = {-1000000000, -1000000000};

	e combine(e l, e r) {
		if (l.a > r.a) return l;
		return r;
	}

    void build(vector<e> &v) {  // build the tree
        for (int i = n; i < 2 * n; i++) t[i] = v[i - n];
        for (int i = n - 1; i > 0; --i) t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    e query(int l, int r) {  // sum on interval [l, r)
        e ansl = null_e;
        e ansr = null_e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = combine(ansl, t[l++]);
            if (r&1) ansr = combine(t[--r], ansr);
        }
        return combine(ansl, ansr);
    }

    segtree(int n):n(n),t(){
        t.resize(n << 1, null_e);
    }
};