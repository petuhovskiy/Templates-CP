struct point {
    ld x, y;
    point(ld x, ld y): x(x), y(y) {}
    point(): x(Nld), y(Nld) {}

    point operator-(const point& to) const {
        return point(x - to.x, y - to.y);
    }

    point operator+(const point& to) const {
        return point(x + to.x, y + to.y);
    }

    ld operator*(const point& to) const {
        return to.x * y - to.y * x;
    }

    ld operator^(const point& to) const {
        return sqrt(sq(x - to.x) + sq(y - to.y));
    }

    bool operator==(const point& to) const {
        return eq(to.x, x) && eq(to.y, y);
    }

    bool isNull() const {
        return isnan(x) || isnan(y);
    }

    point& operator -= (const point& to) {
        return *this = *this - to;
    }

    point& operator += (const point& to) {
        return *this = *this + to;
    }
};

ostream& operator << (ostream &os, const point &p) {
    return os << p.x << " " << p.y;
}

istream& operator >> (istream &is, point &p) {
    return is >> p.x >> p.y;
}
