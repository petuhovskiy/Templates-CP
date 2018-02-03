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
            if (l) sum = F(l->x) + sum;
            if (r) sum = sum + F(r->x);
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

    template <typename T, typename C>
    void walk(T* t, const C& callback) {
        if (!t) return;
        walk(t->l, callback);
        callback(*t);
        walk(t->r, callback);
    }
}
