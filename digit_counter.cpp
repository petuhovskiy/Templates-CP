vector<long long> count(long long r) {
    vector<long long> cnt(10, 0);
    if (r == 0) return cnt;
    long long tmp = r;
    vector<int> v;
    while (tmp > 0) v.pb(tmp % 10), tmp /= 10;
    long long rc = 1;
    long long lc = r / 10;
    long long rr = 0;
    for (int i = 0; i < v.size(); i++) {
        cnt[0] += max(lc - 1, 0ll) * rc;
        for (int c = 1; c < 10; c++) cnt[c] += lc * rc;
        for (int c = (lc > 0 ? 0 : 1); c < v[i]; c++) cnt[c] += rc;
        cnt[v[i]] += rr + 1;
        rr += v[i] * rc;
        rc *= 10;
        lc /= 10;
    }
    return cnt;
}
