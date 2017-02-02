namespace bridges {
    const int N = 1e5 + 5;

    map<int, int> compact(vector<int> &v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        map<int, int> res;
        for (int i = 0; i < v.size(); i++) res[v[i]] = i;
        return res;
    }

    bool gbr[N];
    int fup[N];
    int tin[N];
    bool used[N];
    vector<pair<int, int> > g[N];
    int markysha = 0;

    void dfs(int x, int pr = -1) {
        used[x] = true;
        tin[x] = markysha++;
        fup[x] = tin[x];
        for (auto &it : g[x]) {
            int to, num;
            tie(to, num) = it;
            if (to == pr) continue;
            if (used[to]) {
                fup[x] = min(fup[x], tin[to]);
            } else {
                dfs(to, x);
                fup[x] = min(fup[x], fup[to]);
                if (fup[to] > tin[x]) {
                    gbr[num] = 1;
                }
            }
        }
    }

    vector<bool> find_bridges(vector<pair<int, int>> t) {
        int m = t.size();
        vector<int> allindexes;
        for (auto &it : t) {
            int a, b;
            tie(a, b) = it;
            allindexes.pb(a);
            allindexes.pb(b);
        }
        markysha = 0;
        auto mt = compact(allindexes);
        int n = mt.size();

        fill(gbr, gbr + m, false);
        fill(fup, fup + n, 0);
        fill(used, used + n, 0);

        for (int i = 0; i < n; i++) g[i].clear();
        int jt = 0;
        for (auto &it : t) {
            int a, b;
            tie(a, b) = it;
            a = mt[a];
            b = mt[b];
            if (a > b) swap(a, b);
            it = mp(a, b);
            g[a].eb(b, jt);
            g[b].eb(a, jt);
            jt++;
        }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs(i);
        }
        map<pair<int, int>, int> xex;
        for (int i = 0; i < m; i++) {
            auto it = t[i];
            if (xex.count(it)) {
                gbr[i] = gbr[xex[it]] = false;
            }
            xex[it] = i;
        }
        return vector<bool>(gbr, gbr + m);
    }
};