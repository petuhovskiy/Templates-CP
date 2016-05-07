class fenwick{
public:
    int n;  // array size
    vector<int> t;

    int sum(int r) {
        int ans = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) ans += t[r];
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void inc(int x, int y) {
        for (; x < n; x |= x + 1) t[x] += y;
    }

    fenwick(int n):n(n),t(){
        t.assign(n, 0);
    }
};
