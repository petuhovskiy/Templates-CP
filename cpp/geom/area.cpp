namespace area {
    ld of(const point& p1, const point& p2, const point& p3) {
        return fabs((p2 - p1) * (p3 - p1)) / 2;
    }

    ld of(const vector<point>& p) {
        ld s = 0;
        point last = p.back();
        for (const auto& i : p) {
            s += (i.y + last.y) * (i.x - last.x);
            last = i;
        }
        return fabs(s / 2);
    }
}