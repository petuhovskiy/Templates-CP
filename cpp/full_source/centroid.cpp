#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair

const int N = 3e5;

int sz[N];
bool used[N];
vector<vector<int> > g;

int computeSize(int x, int pr = -1) {
    sz[x] = 1;
    for (int to : g[x]) {
        if (to == pr || used[to]) continue;
        sz[x] += computeSize(to);
    }
    return sz[x];
}

int findCentroid(int x) {
    const int N = sz[x];
    bool run = true;
    int pr = -1;
    while (run) {
        run = false;
        for (int to : g[x]) {
            if (to == pr || used[to]) continue;
            if (sz[to] >= N / 2) {
                pr = x;
                x = to;
                run = true;
                break;
            }
        }
    }
    return x;
}

void solve(int x) {
    computeSize(x);
    x = findCentroid(x);
    //action here

    used[x] = true;
    for (int to : g[x]) {
        if (used[to]) continue;
        solve(to);
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }
    solve(1);
    return 0;
}
