/**
    @author https://github.com/StarOrpheus
*/

class segTree {
public:
    struct item {
        item *l, *r;
        int lv, rv; // field of view
        int ans;
        item() : l(NULL), r(NULL), ans(0) {}
        item(long long lv, long long rv) : l(NULL), r(NULL), lv(lv), rv(rv), ans(0) {}
    };

    typedef item* pitem;

    bool ex(int lv, int rv, int v) {
        return lv <= v && rv >= v;
    }

    void calc(item &v) {
        v.ans = 0;
        if(v.l != NULL) v.ans += v.l->ans;
        if(v.r != NULL) v.ans += v.r->ans;
    }

    item root(1, 1<<30);

    void modify(item& v, int p, int a) {
        if(v.lv == v.rv && v.lv == p) {
            v.ans = p;
            return;
        }
        if(ex(v.lv, (v.lv + v.rv) >> 1, p)) {
            if(v.l == NULL) v.l = new item(v.lv, (v.lv + v.rv) >> 1);
            modify(*v.l, p, a);
        } else {
            if(v.r == NULL) v.r = new item(((v.lv + v.rv) >> 1) + 1, v.rv);
            modify(*v.r, p, a);
        }
        calc(v);
    }

    void modify(int p, int a) {
        modify(root, p, a);
    }

    long long query(item &v, int l, int r) {
        if(r < v.lv || l > v.rv) return 0;
        if(l <= v.lv && r >= v.rv) return v.ans;
        long long res = 0;
        if(v.l != NULL) res += query(*v.l, l, r);
        if(v.r != NULL) res += query(*v.r, l, r);
        return res;
    }

    long long(int l, int r) {
        return query(root, l, r);
    }

    segTree() {}
    segTree(int n) {
        long long z = 1;
        while (z < n) z <<= 1;
        root = item(1, z);
    }

};
