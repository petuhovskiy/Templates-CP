template<typename T>
struct varray{

    T dl;
    int n;
    T *a;
    int *v;
    int cur;

    void nextVersion() {
        cur++;
    }

    T& operator[](int pos) {
        if (v[pos] != cur) {
            v[pos] = cur;
            a[pos] = dl;
        }
        return a[pos];
    }

    varray(int n, T dl): dl(dl), n(n), cur(0) {
        a = new T[n];
        v = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = 0;
            a[i] = dl;
        }
        cur = 0;
    }
};
