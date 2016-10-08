struct sparse_table{
    int n;
    vector<vector<int> > t;

    int query(int l, int r) {
        int sz = r - l + 1;
        int b = 31 - __builtin_clz(sz);
        return max(t[l][b], t[r - (1<<b) + 1][b]);
    }

    sparse_table(vector<int> &v): n(v.size()), t(v.size()) {
        for (int i = 0; i < n; i++) {
            t[i].push_back(v[i]);
        }
        for (int e = 1; (1 << e) <= n; e++) {
            int sz = 1 << e;
            int half = sz >> 1;
            for (int i = 0; i + sz <= n; i++) {
                t[i].push_back(max(t[i][e - 1], t[i + half][e - 1]));
            }
        }
    }
};
