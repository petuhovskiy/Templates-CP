struct segtree{

    int n;
    vector<vector<int> > t;

    void build(vector<int> &v) {
        for (int i = 0; i < n; i++) {
            t[n + i].push_back(v[i]);
        }
        for (int i = n - 1; i > 0; i--) {
            t[i].resize(t[i<<1].size() + t[i<<1|1].size());
            merge(t[i<<1].begin(), t[i<<1].end(), t[i<<1|1].begin(), t[i<<1|1].end(), t[i].begin());
        }
        initCustom();
    }

    void initCustom() {
        //custom code here
    }

    //solve on [l, r)
    int solve(int l, int r) {
        vector<int> roots;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) roots.push_back(l++);
            if (r & 1) roots.push_back(--r);
        }
        //example:
        int mn = 2e9;
        int mx = -2e9;
        for (int num : roots) {
            vector<int> &v = t[num];
            if (v.empty()) continue;
            mn = min(mn, v[0]);
            mx = max(mx, v.back());
        }
        return mx - mn;
    }

    segtree(vector<int> &v) {
        n = v.size();
        t.resize(n << 1);
        build(v);
    }
};
