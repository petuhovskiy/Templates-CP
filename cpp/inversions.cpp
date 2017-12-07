size_t inversions(vector<size_t>& t) {
    if (t.size() < 2) return 0;
    vector<size_t> a(t.begin(), t.begin() + t.size() / 2), b(t.begin() + t.size() / 2, t.end());
    size_t res = 0;
    res += inversions(a);
    res += inversions(b);
    size_t j = 0;
    size_t it = 0;
    for (size_t i = 0; i < b.size(); ++i) {
        while (j < a.size() && a[j] < b[i]) t[it++] = a[j++];
        res += a.size() - j;
        t[it++] = b[i];
    }
    while (j < a.size()) t[it++] = a[j++];
    return res;
}
