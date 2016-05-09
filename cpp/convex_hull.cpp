template <typename T>
struct convex_hull{

    T getIntersectX(pair<T, T> &a, pair<T, T> &b) {
        return (b.second - a.second) / (a.first - b.first);
    }

    vector<pair<T, T> > cvh;

    void addToCVH(pair<T, T> a) {
        while (!cvh.empty()) {
            pair<T, T> &b = cvh.back();
            if (a.first == b.first && a.second >= b.second) return;
            if (a.second < b.second) cvh.pop_back();
            else {
                if (cvh.size() == 1) break;
                else {
                    pair<T, T> &c = cvh[cvh.size() - 2];
                    if (getIntersectX(c, a) <= getIntersectX(c, b)) cvh.pop_back();
                    else break;
                }
            }
        }
        cvh.push_back(a);
    }

    T getY(T x, T k, T b) {
        return k * x + b;
    }

    T getY(T x) {
        int l = 0, r = cvh.size() - 1;
        while (r - l > 2) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            if (getY(x, cvh[m1].first, cvh[m1].second) > getY(x, cvh[m2].first, cvh[m2].second)) {
                l = m1;
            } else {
                r = m2;
            }
        }
        T mn = 1e9;
        for (int i = l; i <= r; i++) {
            mn = min(mn, getY(x, cvh[i].first, cvh[i].second));
        }
        return mn;
    }

    void makeCVH(vector<pair<T, T> > &a) {
        sort(a.rbegin(), a.rend());
        for (int i = 0; i < a.size(); i++) addToCVH(a[i]);
    }
};
