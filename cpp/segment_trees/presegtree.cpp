template<typename T, typename X>
struct presegtree{
    unordered_map<T, X> m;
    int n;
    segtree<X> sg;

    int get(T p) {
        assert(m.count(p));
        return m[p];
    }

    void modify(T p, X value) {
        sg.modify(get(p), value);
    }

    X query(T l, T r) {
        return sg.query(get(l), get(r) + 1);
    }

    X lower(T r) {
        return sg.query(0, get(r) + 1);
    }

    X upper(T l) {
        return sg.query(get(l), n);
    }

    presegtree(vector<T> v, X def = 0): sg(0) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        n = v.size();
        for (int i = 0; i < n; i++) m[v[i]] = i;
        sg = segtree<X>(n, def);
    }
};
