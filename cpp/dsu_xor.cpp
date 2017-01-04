struct dsu{
    int n;
    vector<int> v;
    vector<int> q;

    pair<int, int> froot(int x) {
        if (v[x] == x) return mp(x, q[x]);
        auto it = froot(v[x]);
        v[x] = it.F;
        q[x] ^= it.S;
        return mp(v[x], q[x]);
    }

    void unite(int x, int y) {
        if (rand() & 1) swap(x, y);
        auto f1 = froot(x);
        auto f2 = froot(y);
        if (f1.F == f2.F) return;
        int t = f1.S ^ f2.S ^ 1;
        v[f2.F] = f1.F;
        q[f2.F] = t;
    }

    bool query(int x, int y) {
        auto f1 = froot(x);
        auto f2 = froot(y);
        return f1.S != f2.S;
    }

    dsu(int n): v(n), q(n, 0) {
        for (int i = 0; i < n; i++) v[i] = i;
    }
};
