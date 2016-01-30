class treap{
    struct item{
        int x, y, l, r, k;
    };
private:
    vector<item> t;
public:
    void resize(int num) {
        t.resize(num);
    }

    void init(int v, int x) {
        t[v].x = x;
        t[v].y = rand();
        t[v].l = t[v].r = 0;
        t[v].k = !!v;
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
            split(t[v].r, t[v].r, r, key - t[t[v].l].k - 1);
        } else {
            r = v;
            split(t[v].l, l, t[v].l, key);
        }
        cnt(l);
        cnt(r);
    }

    treap(int num) {
        resize(num);
        init(0, 0);
    }

    void output(int x) {
        if (!x) return;
        output(t[x].l);
        cout << t[x].x << " ";
        output(t[x].r);
    }
};
