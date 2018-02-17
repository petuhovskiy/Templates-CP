template <typename T, typename F>
struct Node {
    Node* l;
    Node* r;
    uint32_t y;
    size_t sz;

    T data;
    F sum;

    Node(const T& data): l(nullptr), r(nullptr), y(rnd()), sz(1), data(data), sum(data) {}
    Node(T&& data): l(nullptr), r(nullptr), y(rnd()), sz(1), data(data), sum(data) {}

    Node* update() {
        sz = size(l) + 1 + size(r);
        sum = F(data);
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
