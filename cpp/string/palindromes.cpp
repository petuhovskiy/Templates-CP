vector<int> p1(n), p2(n);
int l = 0, r = -1;
for (int i = 0; i < n; i++) {
    int k = (i > r ? 1 : min(p1[l + r - i], r - i + 1));
    while (i + k < n && i - k >= 0 && v[i + k] == v[i - k]) k++;
    p1[i] = k--;
    if (i + k > r) {
        l = i - k;
        r = i + k;
    }
}
l = 0;
r = -1;
for (int i = 0; i < n; i++) {
    int k = (i >= r ? 0 : min(p2[l + r - i - 1], r - i));
    while (i - k >= 0 && i + k + 1 < n && v[i - k] == v[i + k + 1]) k++;
    p2[i] = k--;
    if (i + k + 1 > r) {
        l = i - k;
        r = i + k + 1;
    }
}
