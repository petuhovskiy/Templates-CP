#include <bits/stdc++.h>
using namespace std;
#include "segtree.cpp"


struct update {
    long long add;

    bool empty() {
        return false;
    }

    void clear() {
        add = 0;
    }

    void apply(update u) {
        add += u.add;
    }

    update(): add(0) {}
    update(long long add): add(add) {}
};

struct node {
    int sz;
    long long sum;

    bool empty() {
        return sz == 0;
    }

    void apply(update u) {
        sum += u.add * sz;
    }

    node(): sz(0) {}
    node(long long x): sz(1), sum(x) {}
};

node operator + (node l, node r) {
    if (l.empty()) return r;
    if (r.empty()) return l;
    node res;
    res.sz = l.sz + r.sz;
    res.sum = l.sum + r.sum;
    return res;
}

const int N = 100;
const int M = 10000;
const int Z = 100;

segtree<node, update> sg(N, 0);
vector<long long> v(N, 0);

mt19937 rnd(1);

long long query1(int l, int r) {
    long long x = 0;
    for (int i = l; i < r; i++) x += v[i];
    return x;
}

void update1(int l, int r, long long x) {
    for (int i = l; i < r; i++) v[i] += x;
}

int main() {
    for (int i = 0; i < M; i++) {
        int r = rnd() % N;
        int l = rnd() % (r + 1);

        if (rnd() & 1) {
            assert(sg.query(l, r + 1).sum == query1(l, r + 1));
        } else {
            long long x = rnd() % Z;

            update1(l, r + 1, x);
            sg.update(l, r + 1, update(x));
        }
    }
}
