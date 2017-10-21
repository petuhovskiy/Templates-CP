namespace ray {
    bool on(const point& st, point de, point p) {
        if (de == p) return true;
        de = de - st;
        p = p - st;
        return de * p == 0 && signOf(de.x) == signOf(p.x) && signOf(de.y) == signOf(p.y);
    }

    point shot(const point& st, const point& de, ld di) {
        segment s = intersect(circle(st, di), line(st, de));
        return on(st, de, s.a) ? s.a : s.b;
    }
}