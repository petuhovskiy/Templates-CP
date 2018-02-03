namespace treap {
    mt19937 rnd = []() {
        random_device rd;
        return mt19937(rd());
    }();

    template <typename Key, typename F>
    struct Node {
        Node* l;
        Node* r;
        uint32_t y;

        Key x;
        F sum;

        Node(): l(nullptr), r(nullptr), y(rnd()), x(), sum() {}
        Node(const Key& x): l(nullptr), r(nullptr), y(rnd()), x(x), sum(x) {}
        Node(Key&& x): l(nullptr), r(nullptr), y(rnd()), x(x), sum(x) {}

        Node* update() {
            sum = F(x);
            if (l) sum = l->sum + sum;
            if (r) sum = sum + r->sum;
            return this;
        }

        Node* setL(Node* l) {
            this->l = l;
            return update();
        }

        Node* setR(Node* r) {
            this->r = r;
            return update();
        }
    };

    template <typename T>
    T* merge(T* l, T* r) {
        if (!l || !r) return l ? l : r;
        if (l->y > r->y) return l->setR(merge(l->r, r));
        else return r->setL(merge(l, r->l));
    }

    template <typename T, typename Key>
    pair<T*, T*> split(T* t, const Key& x) {
        if (!t) return make_pair(t, t);
        if (t->x < x) {
            auto tmp = split(t->r, x);
            return make_pair(t->setR(tmp.first), tmp.second);
        } else {
            auto tmp = split(t->l, x);
            return make_pair(tmp.first, t->setL(tmp.second));
        }
    }

    template <typename T>
    T* insertOne(T* t, T* e) {
        if (!t) return e;
        if (e->y >= t->y) {
            T *a, *b;
            tie(a, b) = split(t, e->x);
            return e->setL(a)->setR(b);
        } else {
            if (t->x > e->x) {
                return t->setL(insertOne(t->l, e));
            } else {
                return t->setR(insertOne(t->r, e));
            }
        }
    }

    template <typename T, typename Key>
    size_t count(T* t, const Key& x, bool l = false, bool r = false) {
        if (!t) return 0;
        if (l && r) return t->sum.sz;
        if (t->x == x) {
            return 1 + count(t->l, x, l, true) + count(t->r, x, true, r);
        }
        if (t->x > x) {
            return count(t->l, x, l, false);
        } else {
            return count(t->r, x, false, r);
        }
    }

    template <typename T, typename Key>
    T* remove(T* t, const Key& x) {
        if (!t) return t;
        if (t->x == x) return merge(t->l, t->r);
        if (t->x < x) {
            return t->setR(remove(t->r, x));
        } else {
            return t->setL(remove(t->l, x));
        }
    }

    template <typename T, typename C>
    void walk(T* t, const C& callback) {
        if (!t) return;
        walk(t->l, callback);
        callback(*t);
        walk(t->r, callback);
    }
}
