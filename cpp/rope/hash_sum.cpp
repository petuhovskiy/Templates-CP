struct THash {
    size_t sz;
    hesh h;

    bool empty() const {
        return sz == 0;
    }

    THash(): sz(0), h() {}
    THash(char c): sz(1), h(c) {}
};

THash operator + (const THash& l, const THash& r) {
    if (l.empty()) return r;
    if (r.empty()) return l;
    THash res;
    res.sz = l.sz + r.sz;
    res.h = l.h + (r.h << l.sz);
    return res;
}

using node = Node<char, THash>;