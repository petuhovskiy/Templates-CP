const int N = 2e5;
const int L = 32 - __builtin_clz(N);

int timer = 0;
int root = 0;

int tin[N];
int tout[N];
int upv[N][L];

vector<int> go[N];

void dfs(int x, int p = root) {
    tin[x] = timer++;
    upv[x][0] = p;
    for (int i = 1; i < L; i++) upv[x][i] = upv[upv[x][i - 1]][i - 1];
    for (auto to : go[x]) {
        if (to == p) continue;
        dfs(to);
    }
    tout[x] = timer++;
}

bool isupper(int x, int y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int lca(int x, int y) {
    if (tin[x] > tin[y]) swap(x, y);
    if (isupper(x, y)) return x;
    for (int i = L - 1; i >= 0; i--) {
        if (isupper(upv[x][i], y)) continue;
        x = upv[x][i];
    }
    return upv[x][0];
}
