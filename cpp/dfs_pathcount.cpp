const int N = 50500;
vector<pair<int, int> > go[N];
int cntdown[N];
long long lendown[N];
int cntup[N];
long long lenup[N];

void dfs0(int x, int pr = 0) {
    cntdown[x] = 1;
    lendown[x] = 0;
    for (auto &it : go[x]) {
        int to, len;
        tie(to, len) = it;
        if (to == pr) continue;
        dfs0(to, x);
        cntdown[x] += cntdown[to];
        lendown[x] += lendown[to] + cntdown[to] * 1ll * len;
    }
}

void dfs1(int x, int pr = 0) {
    for (auto &it : go[x]) {
        int to, len;
        tie(to, len) = it;
        if (to == pr) continue;
        cntup[to] = cntup[x] + cntdown[x] - cntdown[to];
        lenup[to] = lenup[x] + lendown[x] - lendown[to] - cntdown[to] * 1ll * len + cntup[to] * 1ll * len;
        dfs1(to, x);
    }
}
