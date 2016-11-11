namespace matrix{

    template<typename T>
    void print(vector<vector<T>> &a, ostream &out = cout) {
        for (auto &i : a) {
            for (auto &j : i) out << j << " ";
            out << endl;
        }
    }

    template<typename T>
    void printInfo(const string &info, vector<vector<T>> &a, ostream &out = cout) {
        out << "#########" << info << "#########" << endl;
        print(a, out);
        out << "###END###" << info << "###END###" << endl;
    }

    template<typename T>
    vector<vector<T>> createMatrix(int n, int m, T defaultValue = 0) {
        return vector<vector<T>>(n, vector<T>(m, defaultValue));
    }

    template<typename T>
    vector<vector<T>> createOneMatrix(int n) {
        auto v = createMatrix(n, n, (T)0);
        for (int i = 0; i < n; i++) v[i][i] = 1;
        return v;
    }

    template<typename T>
    vector<vector<T>> createOneMatrixMax(int n) {
        auto v = createMatrix(n, n, (T)-1);
        for (int i = 0; i < n; i++) v[i][i] = 0;
        return v;
    }

    template<typename T>
    vector<vector<T>> mult(vector<vector<T>> &a, vector<vector<T>> &b) {
        int l = a.size();
        int m = a[0].size();
        int n = b[0].size();

        assert(b.size() == m);
        for (auto &it : a) assert(it.size() == m);
        for (auto &it : b) assert(it.size() == n);

        auto res = createMatrix<T>(l, n);
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < n; j++) {
                for (int z = 0; z < m; z++) {
                    res[i][j] += a[i][z] * b[z][j];
                }
            }
        }

        return res;
    }

    template<typename T>
    vector<vector<T>> multMax(vector<vector<T>> &a, vector<vector<T>> &b) {
        int l = a.size();
        int m = a[0].size();
        int n = b[0].size();

        assert(b.size() == m);
        for (auto &it : a) assert(it.size() == m);
        for (auto &it : b) assert(it.size() == n);

        auto res = createMatrix<T>(l, n, -1);
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < n; j++) {
                for (int z = 0; z < m; z++) {
                    if (a[i][z] != -1 && b[z][j] != -1) {
                        res[i][j] = max(res[i][j], a[i][z] + b[z][j]);
                    }
                }
            }
        }

        return res;
    }

    template<typename T>
    vector<vector<T>> binpow(vector<vector<T>> &a, long long t) {
        auto res = createOneMatrix<T>(a.size());
        while (t) {
            if (t & 1) res = mult(res, a);
            a = mult(a, a);
            t >>= 1;
        }
        return res;
    }

    template<typename T>
    vector<vector<T>> binpowMax(vector<vector<T>> &a, long long t) {
        auto res = createOneMatrixMax<T>(a.size());
        while (t) {
            if (t & 1) res = multMax(res, a);
            a = multMax(a, a);
            t >>= 1;
        }
        return res;
    }
};
