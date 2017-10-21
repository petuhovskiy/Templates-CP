namespace convex_hull {
    bool cmp (point a, point b) {
        return a.x < b.x || a.x == b.x && a.y < b.y;
    }

    vector<point> convexHull (vector<point> a) {
        if (a.size() == 1) return a;
        sort(a.begin(), a.end(), &cmp);
        segment line = segment(a[0], a.back());
        vector<point> up, down;
        up.pb(a[0]);
        down.pb(a[0]);
        for (size_t i = 1; i < a.size(); i++) {
            if (line.relationTo(a[i]) <= 0) {
                while (up.size() >= 2 && segment(up[up.size() - 2], up.back()).relationTo(a[i]) <= 0)
                    up.pop_back();
                up.pb(a[i]);
            }
            if (line.relationTo(a[i]) >= 0) {
                while (down.size() >= 2 && segment(down[down.size() - 2], down.back()).relationTo(a[i]) >= 0)
                    down.pop_back();
                down.pb(a[i]);
            }
        }
        for (int i = down.size() - 2; i > 0; --i) up.pb(down[i]);
        if (up.size() == 2 && up[0] == up[1]) up.pop_back();
        return up;
    }
}