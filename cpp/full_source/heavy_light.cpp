#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair

const int N = 200200;
int w[N];

const int EMPTY = -44444;

template<class T>
ostream& operator<<(ostream& out, vector<T>& a) {
    for (int i = 0; i < a.size(); ++i)
        out << a[i] << (i + 1 < a.size() ? " " : "");
    return out;
}

struct e {
    int sz;
    int ans;
    int left;
    int right;
    int sum;

    void apply(int x) {
        if (x == EMPTY) return;
        sum = sz * x;
        left = right = ans = max(x, sum);
    }

    e combine(e l, e r) {
        if (l.sz == 0) return r;
        if (r.sz == 0) return l;
        e res;
        res.sz = l.sz + r.sz;
        res.ans = max(l.ans, max(r.ans, l.right + r.left));
        res.left = max(l.left, l.sum + r.left);
        res.right = max(r.right, r.sum + l.right);
        res.sum = l.sum + r.sum;
        return res;
    }

    void reverse() {
        swap(this->left, this->right);
    }

    e operator+(e r) {
        return combine(*this, r);
    }

    e(): sz(0), ans(0) {}
    e(int x): sz(1), ans(x), left(x), right(x), sum(x) {}
};

class segtree{

public:
    int n;
    vector<e> t;
    vector<int> d;
    int h;

    void build(vector<int> &v) {
        for (int i = n; i < 2 * n; i++) {
            t[i] = e(w[v[i - n]]);
        }
        for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void apply(int p, int value) {
        t[p].apply(value);
        if (p < n) d[p] = value;
    }

    void calc(int p) {
        t[p] = t[p<<1] + t[p<<1|1];
        if (d[p] != EMPTY) t[p].apply(d[p]);
    }

    void resolve(int v) {
        for (v += n; v > 1; ) calc(v >>= 1);
    }

    void push(int v) {
        v += n;
        for (int s = h; s > 0; s--) {
            int i = v >> s;
            if (d[i] != EMPTY) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = EMPTY;
            }
        }
    }

    void modify(int l, int r, int value) {
        push(l);
        push(r - 1);
        int l0 = l, r0 = r;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, value);
            if (r&1) apply(--r, value);
        }
        resolve(l0);
        resolve(r0 - 1);
    }

    e query(int l, int r) {
        push(l);
        push(r - 1);
        e ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = ansl + t[l++];
            if (r&1) ansr = t[--r] + ansr;
        }
        return ansl + ansr;
    }

    segtree(vector<int> &v):t(){
        n = v.size();
        h = 32 - __builtin_clz(n);
        t.resize(n << 1);
        d.assign(n, EMPTY);
        build(v);
    }
};

int tin[N];
int tout[N];
int sz[N];
int up[N];
int cur = 0;
vector<vector<int> > g;

int cp[N];
int pos[N];
int cps = 0;
vector<vector<int> > vert;
vector<segtree> pts;

bool isupper(int x, int y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

void dfs(int x, int pr = -1) {
    up[x] = -1;
    tin[x] = cur++;
    sz[x] = 1;
    up[x] = pr;
    for (int to : g[x]) {
        if (to == pr) continue;
        dfs(to, x);
        sz[x] += sz[to];
    }
    int heavy = -1;
    for (int to : g[x]) {
        if (to == pr) continue;
        if (sz[to] * 2 > sz[x]) {
            heavy = to;
            break;
        }
    }
    if (heavy == -1) {
        vert.pb(vector<int>(1, x));
        cp[x] = cps++;
        pos[x] = 0;
    } else {
        pos[x] = pos[heavy] + 1;
        cp[x] = cp[heavy];
        vert[cp[x]].pb(x);
    }
    tout[x] = cur++;
}

void buildAll() {
    for (int i = 0; i < cps; i++) {
        pts.pb(segtree(vert[i]));
    }
}

void modify(int a, int b, int c) {
    if (tin[a] < tin[b]) swap(a, b);
    while (!isupper(a, b)) {
        int x = cp[a];
        if (isupper(vert[x].back(), b)) {
            int l = pos[a];
            int r = vert[x].size() - 1;
            int ans = pos[a];
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (isupper(vert[x][mid], b)) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            pts[x].modify(pos[a], ans, c);
            a = vert[x][ans];
            break;
        } else {
            pts[x].modify(pos[a], vert[x].size(), c);
            a = up[vert[x].back()];
        }
    }
    int y = cp[a];
    while (true) {
        int x = cp[b];
        if (x == y) {
            pts[x].modify(pos[b], pos[a] + 1, c);
            break;
        } else {
            pts[x].modify(pos[b], vert[x].size(), c);
            b = up[vert[x].back()];
        }
    }
}

e query(int a, int b) {
    e res;
    if (tin[a] < tin[b]) swap(a, b);
    while (!isupper(a, b)) {
        int x = cp[a];
        if (isupper(vert[x].back(), b)) {
            int l = pos[a];
            int r = vert[x].size() - 1;
            int ans = pos[a];
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (isupper(vert[x][mid], b)) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            res = res + pts[x].query(pos[a], ans);
            a = vert[x][ans];
            break;
        } else {
            res = res + pts[x].query(pos[a], vert[x].size());
            a = up[vert[x].back()];
        }
    }
    e res1;
    int y = cp[a];
    while (true) {
        int x = cp[b];
        if (x == y) {
            res1 = res1 + pts[x].query(pos[b], pos[a] + 1);
            break;
        } else {
            res1 = res1 + pts[x].query(pos[b], vert[x].size());
            b = up[vert[x].back()];
        }
    }
    res1.reverse();
    return res + res1;
}

int main(){
    ios_base::sync_with_stdio(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n, q;
    cin >> n >> q;
    g.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(0);
    buildAll();
    for (int i = 0; i < q; i++) {
        int t, a, b, c;
        cin >> t >> a >> b >> c;
        a--;
        b--;
        if (t == 1) {
            modify(a, b, c);
        } else {
            cout << query(a, b).ans << endl;
        }
    }
    return 0;
}
