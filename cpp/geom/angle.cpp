namespace angle {
    ld of(const point& p) {
        ld a = atan(p.y / p.x);
        if (p.y == 0 && p.x > 0) return 0;
        if (p.x < 0) return PI + a;
        if (p.y > 0) return a;
        return 2 * PI + a;
    }

    ld of(const point& a, const point& b) {
        ld x = fabs(of(a) - of(b));
        return min(x, 2 * PI - x);
    }
}