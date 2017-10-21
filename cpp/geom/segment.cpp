struct segment {
    point a, b;
    segment(const point& a, const point& b): a(a), b(b) {}
    segment(): a(), b() {}

    line toLine() const {
        return line(a, b);
    }

    int relationTo(const point& p) const {
        return signOf((b - a) * (p - a));
    }

    bool inBox(const point& p) const {
        return within(p.x, a.x, b.x) && within(p.y, a.y, b.y);
    }

    bool operator == (const segment& s) const {
        return a == s.a && b == s.b;
    }

    bool isNull() const {
        return a.isNull() || b.isNull();
    }
};

point intersect(const segment& s, const point& p) {
    if (s.inBox(p) && s.relationTo(p) == 0) return p;
    return point();
}

ld operator ^ (const segment& s, const point& p) {
    point x = s.toLine().projection(p);
    if (intersect(s, x).isNull()) return min(p ^ s.a, p ^ s.b);
    return x ^ p;
}

segment intersect(const segment& x, const segment& y) {
    if (x.a == x.b) {
        if (y.a == y.b) {
            return x == y ? x : segment();
        }
        point p = intersect(y, x.a);
        return segment(p, p);
    }
    if (y.a == y.b) return intersect(y, x);
    line l1 = x.toLine();
    line l2 = y.toLine();
    if (l1 == l2) {
        if (eq(l1.b, 0)) {
            pld f = intersectProj(x.a.y, x.b.y, y.a.y, y.b.y);
            if (isnan(f)) return segment();
            return segment(point(l1.findX(f.F), f.F), point(l1.findX(f.S), f.S));
        }
        pld f = intersectProj(x.a.x, x.b.x, y.a.x, y.b.x);
        if (isnan(f)) return segment();
        return segment(point(f.F, l1.findY(f.F)), point(f.S, l1.findY(f.S)));
    }
    point p = intersect(l1, l2);
    if (p.isNull()) return segment();
    if (x.inBox(p) && y.inBox(p)) return segment(p, p);
    return segment();
}

ostream& operator << (ostream& os, const segment& s) {
    return os << "segment{a=(" << s.a << "), b=(" << s.b << ")}";
}
