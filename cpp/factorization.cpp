#include <bits/stdc++.h>

using namespace std;

namespace Factorization{
    const int SN = 10000000;
    int lp[SN];
    vector<int> pr;

    bool init_sieve() {
        for (int i = 2; i < SN; i++) {
            if (!lp[i]) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (int j = 0; j < pr.size() && pr[j] <= lp[i] && 1ll * i * pr[j] < SN; j++)
                lp[i * pr[j]] = pr[j];
        }
    }
    bool __init_sieve = init_sieve();

    vector<pair<int, int> > factorize(int x) {
        vector<pair<int, int> > res;
        while (x > 1) {
            int cur = lp[x];
            int cnt = 0;
            while (lp[x] == cur) {
                cnt++;
                x /= cur;
            }
            res.push_back(make_pair(cur, cnt));
        }
        return res;
    }

    vector<int> getDivisorsOf(int x) {
        vector<int> res(1, 1);
        auto f = factorize(x);
        for (auto &it : f) {
            int sz = res.size();
            res.reserve(sz * (it.second + 1));
            int cur = 1;
            for (int j = 0; j < it.second; j++) {
                cur *= it.first;
                for (int i = 0; i < sz; i++) res.push_back(res[i] * cur);
            }
        }
        return res;
    }
}

int main() {
    vector<int> f = Factorization::getDivisorsOf(20);
    sort(f.begin(), f.end());
    assert(f == ((vector<int>){1, 2, 4, 5, 10, 20}));
}
