template<typename T>
struct varray{

    T dl;
    int n;
    vector<T> a;
    vector<int> v;
    int cur;

    inline void fill() {
        cur++;
    }

    inline void fill(T d) {
        dl = d;
        cur++;
    }

    inline T& operator[](int pos) {
        if (v[pos] != cur) {
            v[pos] = cur;
            a[pos] = dl;
        }
        return a[pos];
    }

    varray(int n, T dl): dl(dl), n(n), cur(0), a(n, dl), v(n, 0) {}
};
