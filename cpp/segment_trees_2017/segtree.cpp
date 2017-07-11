template<typename T, typename U>
struct segtree {

	int n;
	int h;

	std::vector<T> t;
	std::vector<U> u;

	template<typename U2>
	void apply(int x, U2 upd) {
		t[x].apply(upd);
		if (x < n) u[x].apply(upd);
	}

	void push(int x) {
		for (int i = h; i > 0; i--) {
			int y = x >> i;
			if (!u[y].empty()) {
				apply(y << 1, u[y]);
				apply(y << 1 | 1, u[y]);
				u[y].clear();
			}
		}
	}

	void recalc(int x) {
		while ((x >>= 1) > 0) {
			t[x] = t[x << 1] + t[x << 1 | 1];
			t[x].apply(u[x]);
		}
	}

	template<typename U2>
	void update(int l, int r, U2 upd) {
		l += n; r += n;
		int l0 = l, r0 = r - 1;
		push(l0); push(r0);
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) apply(l++, upd);
			if (r & 1) apply(--r, upd);
		}
		recalc(l0); recalc(r0);
	}

	T query(int l, int r) {
		l += n; r += n;
		push(l); push(r - 1);
		T al, ar;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) al = al + t[l++];
			if (r & 1) ar = t[--r] + ar;
		}
		return al + ar;
	}

	void rebuildLayers() {
		for (int i = n - 1; i > 0; i--) {
			t[i] = t[i << 1] + t[i << 1 | 1];
		}
	}

	segtree(int n) : n(n), t(n << 1), u(n), h(32 - __builtin_clz(n)) {}
	segtree(std::vector<T> v) : segtree(v.size()) {
		std::copy(v.begin(), v.end(), t.begin() + n);
		rebuildLayers();
	}
	segtree(int n, T def) : segtree(std::vector<T>(n, def)) {}
};
