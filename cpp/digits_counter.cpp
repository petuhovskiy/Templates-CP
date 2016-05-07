vector<long long> count(long long r) {
    vector<long long> ans(10, 0);
    if (r == 0) return ans;
    long long tmp = r;
    vector<int> v;
    while (tmp > 0) {
        v.push_back(tmp % 10);
        tmp /= 10;
    }
    long long right = 1;
    long long left = r / 10;
    long long cnt = 0;
    for (int i = 0; i < v.size(); i++) {
        ans[0] += max(left - 1, 0ll) * right;
        for (int digit = 1; digit < 10; digit++) {
            ans[digit] += left * right;
        }
        for (int digit = !left; digit < v[i]; digit++) {
            ans[digit] += right;
        }
        ans[v[i]] += cnt + 1;
        cnt += v[i] * right;
        right *= 10;
        left /= 10;
    }
    return ans;
}
