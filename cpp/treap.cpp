unsigned int rnd() {
    unsigned int y = rand();
    y <<= 16;
    y |= rand();
    return y;
}

struct treap{

    struct item{
        int x, l, r, y;
        item(int x): x(x), l(0), r(0), y(rnd()) {}
    };

    vector<item> t;

    inline item& operator[](int i) {
        return t[i];
    }

    inline void apply(int v/*, int add*/) {
        //t[v].add += add;
    }

    inline void push(int v) {
        if (v) {
            if (t[v].l) apply(t[v].l/*, t[v].add*/);
            if (t[v].r) apply(t[v].r/*, t[v].add*/);
            //t[v].add = 0;
        }
    }

    int add(item i) {
        t.push_back(i);
        return t.size() - 1;
    }

    int add(int key) {
        return add(item(key));
    }

    void merge(int &v, int l, int r) {
        push(l);
        push(r);
        if (!l || !r) {
            v = l | r;
        } else if (t[l].y > t[r].y) {
            v = l;
            merge(t[l].r, t[l].r, r);
        } else {
            v = r;
            merge(t[r].l, l, t[r].l);
        }
    }

    void split(int v, int &l, int &r, int key) {
        if (v) {
            push(v);
            if (t[v].x < key) {
                l = v;
                split(t[l].r, t[l].r, r, key);
            } else {
                r = v;
                split(t[r].l, l, t[r].l, key);
            }
        } else {
            l = r = 0;
        }
    }

    void insert2(int &v, int x) {
        if (v) {
            push(v);
            if (t[x].y > t[v].y) {
                split(v, t[x].l, t[x].r, t[x].x);
                v = x;
            } else {
                insert(t[x].x < t[v].x ? t[v].l : t[v].r, x);
            }
        } else {
            v = x;
        }
    }

    inline void insert(int &v, int x) {
        if (v) {
            int t1;
            split(v, v, t1, t[x].x);
            merge(v, v, x);
            merge(v, v, t1);
        } else {
            v = x;
        }
    }

    void transfer(int from, int &to) {
        if (!from) return;
        queue<int> q;
        q.push(from);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            push(v);
            if (t[v].l) q.push(t[v].l);
            if (t[v].r) q.push(t[v].r);
            t[v].l = t[v].r = 0;
            insert(to, v);
        }
    }

    void unite(int &v, int l, int r) {
        if (!l || !r) {
            v = l | r;
        } else {
            push(l);
            push(r);
            if (t[l].y < t[r].y) swap(l, r);
            int lx, rx;
            split(r, lx, rx, t[l].x);
            unite(t[l].l, t[l].l, lx);
            unite(t[l].r, t[l].r, rx);
            v = l;
        }
    }

    template<typename F>
    void walk(int v, F &lambda) {
        if (v) {
            push(v);
            walk(t[v].l, lambda);
            lambda(t[v]);
            walk(t[v].r, lambda);
        }
    }

    treap() {
        t.push_back(item(0));
    }
};
