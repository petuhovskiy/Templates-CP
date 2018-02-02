const int N = 1e5 + 5;

vector<int> g[N];
vector<pair<int, int>> evs;
int tin[2 * N];
int tout[2 * N];

void dfs(int x, int h = 0) {
    tin[x] = evs.size();
    evs.emplace_back(h, x);
    for (int to : g[x]) {
        dfs(to, h + 1);
        evs.emplace_back(h, x);
    }
    tout[x] = evs.size();
}

sparse_table<pair<int, int>, min> st({});

void buildLCA(int root = 0) {
    dfs(root);
    st = sparse_table<pair<int, int>, min>(evs);
}

int lca(int x, int y) {
    if (tin[x] > tin[y]) swap(x, y);
    return st.query(tin[x], tout[y]).second;
}
