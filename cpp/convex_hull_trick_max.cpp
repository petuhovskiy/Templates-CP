template <typename T>
struct convex_hull{

    deque<pair<T, T> > cvh;

    void pushFront(pair<T, T> a) {
        while (cvh.size() > 1) {
            pair<T, T> &b = cvh[0];
            pair<T, T> &c = cvh[1];
            if ((c.second - a.second) * (b.first - c.first) >= (c.second - b.second) * (a.first - c.first)) cvh.pop_front();
            else break;
        }
        cvh.push_front(a);
    }

    void pushBack(pair<T, T> a) {
        while (cvh.size() > 1) {
            pair<T, T> &b = cvh[cvh.size() - 1];
            pair<T, T> &c = cvh[cvh.size() - 2];
            if ((c.second - a.second) * (b.first - c.first) <= (c.second - b.second) * (a.first - c.first)) cvh.pop_back();
            else break;
        }
        cvh.push_back(a);
    }

    T getY(T x, T k, T b) {
        return k * x + b;
    }

    T getY(T x) {
        T mx = numeric_limits<T>::min();
        int l = 0, r = cvh.size() - 1;
        while (l <= r) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            T r1 = getY(x, cvh[m1].first, cvh[m1].second);
            T r2 = getY(x, cvh[m2].first, cvh[m2].second);
            mx = max(mx, max(r1, r2));
            if (r1 < r2) l = m1 + 1;
            else r = m2 - 1;
        }
        return mx;
    }
};
