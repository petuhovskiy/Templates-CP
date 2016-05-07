struct treap{

    struct item{
        int x, y, l, r, k;

        int rnd() {
            return (rand() << 16) | rand();
        }

        item(int x, int k): x(x), y(rnd()), k(k), l(0), r(0) {}
        item() {}
    };

    vector<item> t;
    int it = 1;

    int add(int x) {
        if (it >= t.size()) t.resize(it + 1);
        t[it] = item(x, 1);
        return it++;
    }

    void cnt(int v) {
        t[v].k = v ? t[t[v].l].k + t[t[v].r].k + 1 : 0;
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
        if (t[t[v].l].k + 1 <= key) {
            l = v;
            split(t[v].r, t[l].r, r, key - t[t[v].l].k - 1);
        } else {
            r = v;
            split(t[v].l, l, t[r].l, key);
        }
        cnt(l);
        cnt(r);
    }

    treap(int num) {
        t.resize(num + 1);
        t[0] = item(0, 0);
    }

    void output(int x) {
        if (!x) return;
        output(t[x].l);
        cout << t[x].x << " ";
        output(t[x].r);
    }
};
