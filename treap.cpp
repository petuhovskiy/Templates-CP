class treap{
    struct item{
        int x, y, l, r, mn;
    };
private:
    vector<item> t;
    int it = 1;
public:
    void resize(int num) {
        t.resize(num);
    }

    void init(int v, int x) {
        t[v].x = x;
        t[v].y = rand();
        t[v].l = t[v].r = 0;
        t[v].mn = x;
    }

    int add(int x) {
        init(it, x);
        return it++;
    }

    void cnt(int v) {
        t[v].mn = min(t[v].x, min(t[t[v].l].mn, t[t[v].r].mn));
    }

    void merge(int &v, int l, int r) {
        if (!l || !r) {
            v = l ? l : r;
        } else if (t[l].y > t[r].y) {
            v = l;
            merge(t[l].r, t[l].r, r);
        } else {
            v = r;
            merge(t[r].l, l, t[r].l);
        }
        cnt(v);
    }

    void split(int v, int &l, int &r, int key) {
        if (!v) {
            l = r = 0;
            return;
        }
        if (t[v].x <= key) {
            l = v;
            split(t[v].r, t[v].r, r, key);
        } else {
            r = v;
            split(t[v].l, l, t[v].l, key);
        }
        cnt(l);
        cnt(r);
    }

    void insert(int &v, int e) {
        if (!v) {
            v = e;
            return;
        }
        if (t[e].y > t[v].y) {
            split(v, t[e].l, t[e].r, t[e].x);
            v = e;
        } else {
            insert(t[e].x <= t[v].x ? t[v].l : t[v].r, e);
        }
    }

    int get(int x) {
        return t[x].mn;
    }

    treap(int num) {
        resize(num);
        init(0, 2e9);
    }

    void output(int x) {
        if (!x) return;
        output(t[x].l);
        cout << t[x].x << " ";
        output(t[x].r);
    }
};
