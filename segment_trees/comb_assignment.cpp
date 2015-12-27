struct e {
	int sz;
	int l, r;
	int k[10][10];
};

class segtree{

public:
  int n;  // array size
  vector<e> t;
  vector<int> d;
  int h;

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
    res.l = l.l;
    res.r = r.r;
    for (int i = 0; i < 10; i++)
      for (int j = 0; j < 10; j++) res.k[i][j] = l.k[i][j] + r.k[i][j];
    res.k[l.r][r.l]++;
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
      t[i].l = t[i].r = v[i - n];
    }
    for (int i = n - 1; i > 0; --i) combine(t[i<<1], t[i<<1|1], t[i]);
  }

  void apply(int p, int value, int k) {
    t[p].sz = k;
    t[p].l = t[p].r = value;
    for (int i = 0; i < 10; i++)
      for (int j = 0; j < 10; j++) t[p].k[i][j] = 0;
    t[p].k[value][value] += k - 1;
    if (p < n) d[p] = value;
  }

  void calc(int p, int k) {
    if (d[p] == -1) combine(t[p<<1], t[p<<1|1], t[p]);
    else apply(p, d[p], k);
  }

  void resolve(int l, int r) {
    int k = 2;
    for (l += n, r += n-1; l > 1; k <<= 1) {
      l >>= 1, r >>= 1;
      for (int i = r; i >= l; i--) calc(i, k);
    }
  }

  void push(int l, int r) {
    int s = h, k = 1 << (h - 1);
    for (l += n, r += n - 1; s > 0; --s, k >>= 1)
      for (int i = l >> s; i <= r >> s; i++)
        if (d[i] != -1) {
          apply(i<<1, d[i], k);
          apply(i<<1|1, d[i], k);
          d[i] = -1;
        }
  }

  void modify(int l, int r, int value) {
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

  void query(int l, int r, e &res) {  // sum on interval [l, r)
    push(l, l + 1);
    push(r - 1, r);
    e ansl, ansr;
    ansl.sz = ansr.sz = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) combine_left(ansl, t[l++]);
      if (r&1) combine_right(t[--r], ansr);
    }
    combine(ansl, ansr, res);
  }

  segtree(int n):n(n),t(){
    h = 32 - __builtin_clz(n);
    t.resize(n << 1);
    d.resize(n, -1);
  }
};
