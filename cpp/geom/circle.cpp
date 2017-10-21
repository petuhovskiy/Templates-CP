struct circle {
    point center;
    ld radius;
    circle(const point& center, ld radius): center(center), radius(radius) {}
    circle(): center(), radius(Nld) {}

    bool operator == (const circle& c) const {
        return center == c.center && eq(radius, c.radius);
    }

    bool isNull() const {
        return center.isNull() || isnan(radius);
    }
};

segment intersect(const circle& c, const line& l) {
    if (!eq(l.a, 0)) {
        ld ta, tb, tc;
        ta = (sq(l.b) / sq(l.a)) + 1;
        tb = 2 * l.b * l.c / sq(l.a);
        tb += 2 * l.b * c.center.x / l.a;
        tb -= 2 * c.center.y;
        tc = sq(c.center.x);
        tc += sq(c.center.y);
        tc += 2 * l.c * c.center.x / l.a;
        tc += sq(l.c) / sq(l.a);
        tc -= sq(c.radius);
        pld ans = solveSquare(ta, tb, tc);
        if (isnan(ans)) return segment();
        ld x0 = (-l.b * ans.F - l.c) / l.a;
        ld x1 = (-l.b * ans.S - l.c) / l.a;
        return segment(point(x0, ans.F), point(x1, ans.S));
    }
    ld y = (-l.c) / l.b;
    ld ta, tb, tc;
    ta = 1;
    tb = -2 * c.center.x;
    tc = sq(c.center.x) + sq(y) + sq(c.center.y) - 2 * y * c.center.y - sq(c.radius);
    pld ans = solveSquare(ta, tb, tc);
    if (isnan(ans)) return segment();
    return segment(point(ans.F, y), point(ans.S, y));
}

vector<point> intersect(const circle& c, const segment& s) {
    segment t = intersect(c, s.toLine());
    vector<point> v;
    if (s.inBox(t.a)) v.pb(t.a);
    if (!(t.b == t.a) && s.inBox(t.b)) v.pb(t.b);
    return v;
}

segment intersect (circle c1, circle c2) {
    point p = c1.center;
    c1.center -= p;
    c2.center -= p;
    auto tmp = intersect(
        c1,
        line(
            -2 * c2.center.x,
            -2 * c2.center.y,
            sq(c2.center.x) + sq(c2.center.y) + sq(c1.radius) - sq(c2.radius)
        )
    );
    if (!tmp.isNull()) {
        tmp.a += p;
        tmp.b += p;
    }
    return tmp;
}
