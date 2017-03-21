namespace hashes {
    typedef ModInt<1000000007> mint1;
    typedef ModInt<1000000009> mint2;

    struct hesh {
        mint1 a;
        mint2 b;

        hesh(): a(0), b(0) {}
        hesh(char x): a(x - 'a' + 1), b(x - 'a' + 1) {}
        hesh(mint1 a, mint2 b): a(a), b(b) {}
    };

    const int BASE1 = 37;
    const int BASE2 = 41;

    const hesh BASE(BASE1, BASE2);

    hesh operator*(hesh a, hesh b) {
        return hesh(a.a * b.a, a.b * b.b);
    }

    hesh operator/(hesh a, hesh b) {
        return hesh(a.a / b.a, a.b / b.b);
    }

    hesh operator+(hesh a, hesh b) {
        return hesh(a.a + b.a, a.b + b.b);
    }

    hesh operator-(hesh a, hesh b) {
        return hesh(a.a - b.a, a.b - b.b);
    }

    hesh st[N];

    bool __initst = [&]() {
        st[0] = hesh(1, 1);
        for (int i = 1; i < N; i++) {
            st[i] = st[i - 1] * BASE;
        }
        return true;
    }();

    hesh operator<<(hesh x, int t) {
        return x * st[t];
    }

    hesh operator>>(hesh x, int t) {
        return x / st[t];
    }

    bool operator<(hesh a, hesh b) {
        if (a.a.x != b.a.x) return a.a.x < b.a.x;
        return a.b.x < b.b.x;
    }

    ostream& operator<<(ostream& o, hesh a) {
        o << "{" << a.a.x << "; " << a.b.x << "}";
        return o;
    }
};
using hesh = hashes::hesh;
