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

    Node* clone() const {
        return new Node(*this);
    }

    Node* update() {
        sum = F(x);
        if (l) sum = l->sum + sum;
        if (r) sum = sum + r->sum;
        return this;
    }

    Node* setL(Node* l) {
        Node* t = clone();
        t->l = l;
        return t->update();
    }

    Node* setR(Node* r) {
        Node* t = clone();
        t->r = r;
        return t->update();
    }
};