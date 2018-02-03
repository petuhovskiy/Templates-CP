#include <bits/stdc++.h>
#include "treap_sum.cpp"

using namespace std;
using namespace treap;

template <typename T>
struct MultisetUnique {
    size_t sz;
    size_t unique;
    T l;
    T r;

    bool empty() {
        return sz == 0;
    }

    MultisetUnique(): sz(0), unique(0) {}
    MultisetUnique(const T& t): sz(1), unique(1), l(t), r(t) {}
};

template <typename T>
MultisetUnique<T> operator + (const MultisetUnique<T>& l, const MultisetUnique<T>& r) {
    if (l.empty()) return r;
    if (r.empty()) return l;
    MultisetUnique<T> res;
    res.sz = l.sz + r.sz;
    res.unique = l.unique + r.unique - (l.r == r.l);
    res.l = l.l;
    res.r = r.r;
    return res;
}

using node = Node<int, MultisetUnique<int>>;
