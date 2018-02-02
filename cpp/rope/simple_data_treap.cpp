namespace treap {
    mt19937 rnd = []() {
        random_device rd;
        return mt19937(rd());
    }();

    template <typename T>
    struct Node {
        Node* l;
        Node* r;
        uint32_t y;
        size_t sz;

        T data;

        Node(): l(nullptr), r(nullptr), y(rnd()), sz(1), data() {}
        Node(const T& data): l(nullptr), r(nullptr), y(rnd()), sz(1), data(data) {}
        Node(T&& data): l(nullptr), r(nullptr), y(rnd()), sz(1), data(data) {}

        Node* update() {
            sz = size(l) + 1 + size(r);
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
    size_t size(T* t) {
        if (!t) return 0;
        return t->sz;
    }

    template <typename T>
    T* merge(T* l, T* r) {
        if (!l || !r) return l ? l : r;
        if (l->y > r->y) return l->setR(merge(l->r, r));
        else return r->setL(merge(l, r->l));
    }

    template <typename T>
    pair<T*, T*> split(T* t, size_t sz) {
        if (!t) return make_pair(t, t);
        if (size(t->l) < sz) {
            auto tmp = split(t->r, sz - 1 - size(t->l));
            return make_pair(t->setR(tmp.first), tmp.second);
        } else {
            auto tmp = split(t->l, sz);
            return make_pair(tmp.first, t->setL(tmp.second));
        }
    }

    template <typename T>
    tuple<T*, T*, T*> cut(T* t, size_t l, size_t r) {
        T *a, *b, *c;
        tie(a, b) = split(t, l);
        tie(b, c) = split(b, r - l);
        return make_tuple(a, b, c);
    }

    template <typename T, typename C>
    void walk(T* t, const C& callback) {
        if (!t) return;
        walk(t->l, callback);
        callback(*t);
        walk(t->r, callback);
    }

    const auto printData = [](const node& n) {
        cout << n.data << " ";
    };
}

using namespace treap;
using node = Node<int>;
