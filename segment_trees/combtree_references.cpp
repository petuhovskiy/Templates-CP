class segtree{

struct e {
	int sz, ans;
};

public:
    int n;  // array size
    vector<e> t;

	void combine(e &l, e &r, e &res) {
	    if (l.sz == 0) {
                res = r;
                return;
	    }
	    if (r.sz == 0) {
                res = l;
                return;
	    }
            res.sz = l.sz + r.sz;
            res.ans = l.ans + r.ans;
	}

	void combine_left(e &l, e &r) {
            e res;
            combine(l, r, res);
            l = res;
	}

	void combine_right(e &l, e &r) {
            e res;
            combine(l, r, res);
            r = res;
	}

    void build(vector<int> &v) {  // build the tree
        for (int i = n; i < 2 * n; i++) {
            t[i].sz = 1;
            t[i].ans = v[i - n];
        }
        for (int i = n - 1; i > 0; --i) combine(t[i<<1], t[i<<1|1], t[i]);
    }

    void modify(int p, int value) {  // set value at position p
        for (t[p += n].ans = value; p >>= 1; ) combine(t[p<<1], t[p<<1|1], t[p]);
    }

    int query(int l, int r) {  // sum on interval [l, r)
        e ansl, ansr;
        ansl.sz = ansr.sz = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) combine_left(ansl, t[l++]);
            if (r&1) combine_right(t[--r], ansr);
        }
        combine_left(ansl, ansr);
        return ansl.ans;
    }

    segtree(int n):n(n),t(){
        t.resize(n << 1);
    }
};
