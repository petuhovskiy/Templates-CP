class dsu{
public:
    int n;  // array size
    vector<int> t;
    vector<int> r;

    int get(int x) {
        return t[x] == x ? x : t[x] = get(t[x]);
    }

    void unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (r[x] <= r[y]) {
            t[x] = y;
            r[y] += r[x] == r[y];
        } else t[y] = x;
    }

    dsu(int n):n(n),t(){
        t.resize(n);
        r.assign(n, 0);
        for (int i = 0; i < n; i++) t[i] = i;
    }
};
