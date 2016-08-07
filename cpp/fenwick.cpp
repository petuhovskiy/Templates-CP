template<typename T>
struct fenwick{
    int n;
    vector<T> t;

    T sum(int r) {
        if (r < 0) return 0;
        r = min(r, n - 1);
        T ans = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) ans += t[r];
        return ans;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void inc(int x, T y) {
        for (; x < n; x |= x + 1) t[x] += y;
    }

    fenwick(int n): n(n), t(n, 0) {}
};
