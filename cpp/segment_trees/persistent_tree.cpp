struct e{
    e *l;
    e *r;
    int ans, sz;

    e() {
        this->l = this->r = 0;
        this->ans = 0;
        this->sz = 1;
    }
};

struct result{
    int ans, sz;
};

class segtree{
public:
    int n;
    vector<e*> roots;

    void update(e *node) {
        e *l = node->l;
        e *r = node->r;
        if (l == 0 && r == 0) {
            node->sz = node->ans = 0;
            return;
        }
        if (l == 0 || r == 0) {
            e *res = l == 0 ? r : l;
            node->sz = res->sz;
            node->ans = res->ans;
            return;
        }
        node->sz = l->sz + r->sz;
        node->ans = l->ans + r->ans;
    }

    void init(e *node, int h) {
        if (--h > 0) {
            node->l = new e();
            node->r = new e();
            init(node->l, h);
            init(node->r, h);
            update(node);
        }
    }

    segtree(int n) {
        this->n = 1<<(32 - __builtin_clz(n - 1));
        roots.push_back(new e());
        init(roots[0], 32 - __builtin_clz(this->n));
    }

    e* modify(e *node, int l, int r, int x, int y) {
        e *mod = new e();
        if (l == r) {
            mod->ans = y;
            return mod;
        }
        if (x - l < r - x) {
            mod->l = modify(node->l, l, (l + r)>>1, x, y);
            mod->r = node->r;
        } else {
            mod->l = node->l;
            mod->r = modify(node->r, ((l + r)>>1) + 1, r, x, y);
        }
        update(mod);
        return mod;
    }

    result query(e *node, int dl, int dr, int l, int r) {
        if (l > r) return {0, 0};
        if (dl == l && dr == r) {
            return {node->ans, node->sz};
        }
        int mid = (dl + dr)>>1;
        result lv = query(node->l, dl, mid, l, min(r, mid));
        result rv = query(node->r, mid + 1, dr, max(l, mid + 1), r);
        return {lv.ans + rv.ans, lv.sz + rv.sz};
    }

    void modify(int x, int y) {
        roots.push_back(modify(roots[roots.size() - 1], 1, n, x, y));
    }
};
