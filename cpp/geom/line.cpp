struct line {
    ld a, b, c;
    line(ld a, ld b, ld c): a(a), b(b), c(c) {}
    line(): a(Nld), b(Nld), c(Nld) {}

    line(const point& p1, const point& p2) {
        if (!eq(p1.y, p2.y)) {
            a = 1;
            b = (p1.x - p2.x) / (p2.y - p1.y);
        } else {
            b = 1;
            a = (p2.y - p1.y) / (p1.x - p2.x);
        }
        c = -(a * p1.x + b * p1.y);
    }

    point projection(const point& p) const {
        ld t = -(a * p.x + b * p.y + c) / (sq(a) + sq(b));
        return point(p.x + t * a, p.y + t * b);
    }

    line parallelOf(point p) const {
        return line(a, b, -(a * p.x + b * p.y));
    }

    ld findX(ld y) const {
        return (-b * y - c) / a;
    }

    ld findY(ld x) const {
        return (-a * x - c) / b;
    }

    line rotate90() const {
        return line(point(0, 0), point(a, b));
    }

    int relationTo(const point& p) const {
        return signOf(a * p.x + b * p.y + c);
    }

    bool operator == (const line& to) const {
        return eq(a, to.a) && eq(b, to.b) && eq(c, to.c);
    }

    bool isNull() const {
        return isnan(a) || isnan(b) || isnan(c);
    }
};

point intersect(line t1, line t2) {
    point r;
    if (eq(t2.a * t1.b - t2.b * t1.a, 0)) return r;
    if (eq(t1.a, 0)) swap(t1, t2);  // TODO: const w/out swap
    r.y = (t1.a * t2.c - t1.c * t2.a) / (t2.a * t1.b - t2.b * t1.a);
    r.x = (t1.b * r.y + t1.c) / (-t1.a);
    return r;
}

istream& operator >> (istream& is, line& l) {
    return is >> l.a >> l.b >> l.c;
}

ostream& operator << (ostream& out, const line& l) {
    return out << "line{a=" << l.a << ", b=" << l.b << ", c=" << l.c << "}";
}
