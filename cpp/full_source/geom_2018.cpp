#include <bits/stdc++.h>

using namespace std;

using ld = long double;

const ld NaN = numeric_limits<ld>::quiet_NaN();
// const ld INF = numeric_limits<ld>::max();
const ld INF = 1e12;
const ld EPS = 1e-10;
const ld PI = acos(-1);

ld sqr(const ld& x) {
    return x * x;
}

ld eql(const ld& a, const ld& b) {
    return fabs(b - a) < EPS;
}

ld leq(const ld& a, const ld& b) {
    return a - b < EPS;
}

ld geq(const ld& a, const ld& b) {
    return b - a < EPS;
}

ld neq(const ld& a, const ld& b) {
    return fabs(b - a) >= EPS;
}

bool inside(ld l, ld r, const ld& a) {
    if (l > r) {
        swap(l, r);
    }
    return leq(l, a) && leq(a, r);
}

int sgn(const ld& a) {
    if (a > EPS) return 1;
    if (a < -EPS) return -1;
    return 0;
}

struct Point;
struct Segment;
struct Line;
struct Circle;

struct Point {
    ld x;
    ld y;

    Point(): x(NaN), y(NaN) {}
    Point(ld x, ld y): x(x), y(y) {}

    bool null() const;
    ld sq() const;
    ld length() const;
    Point rotate90() const;  // rotates CCW
    ld scalar(const Point& p) const;
    ld vect(const Point& p) const;
    int relationTo(const Point& p) const;
};

struct Segment {
    Point a;
    Point b;

    Line toLine() const;
    bool inBox(const Point& p) const;
    int relationTo(const Point& p) const;
};

struct Line {
    ld a;
    ld b;
    ld c;

    Line(const Point& a, const Point& b);
    Line(ld a, ld b, ld c): a(a), b(b), c(c) {
        ld len = length();
        this->a /= len;
        this->b /= len;
        this->c /= len;
    }
    Line(const Point& p, const ld& c): Line(p.x, p.y, c) {}

    ld sq() const;
    ld length() const;
    Point norm() const;
    Point direction() const;
    Point projection(const Point& p) const;
    Line rotate90() const;
    Line shiftedTo(const Point& p) const;
    Line shiftedOn(const Point& p) const;
    Point anyPoint() const;

    ld calc(const Point& p) const;
};

struct Circle {
    Point p;
    ld r;
};

istream& operator >> (istream& in, Point& p) {
    return in >> p.x >> p.y;
}

istream& operator >> (istream& in, Segment& sg) {
    return in >> sg.a >> sg.b;
}

istream& operator >> (istream& in, Circle& c) {
    return in >> c.p >> c.r;
}

ostream& operator << (ostream& out, const Point& p) {
#ifdef LOCAL
    return out << "(" << p.x << " " << p.y << ")";
#else
    return out << p.x << " " << p.y;
#endif
}

ostream& operator << (ostream& out, const Line& l) {
#ifdef LOCAL
    return out << "Line " << l.a << " " << l.b << " " << l.c;
#else
    return out << l.a << " " << l.b << " " << l.c;
#endif
}

template <typename T>
ostream& operator << (ostream& out, const vector<T>& v) {
    out << "[";
    copy(v.begin(), v.end(), ostream_iterator<T>(out, " "));
    out << "]";
    return out;
}

Point& operator += (Point& r, const Point& pt) {
    r.x += pt.x;
    r.y += pt.y;
    return r;
}

Point& operator -= (Point& r, const Point& pt) {
    r.x -= pt.x;
    r.y -= pt.y;
    return r;
}

Point& operator *= (Point& r, const ld& l) {
    r.x *= l;
    r.y *= l;
    return r;
}

Point& operator /= (Point& r, const ld& l) {
    r.x /= l;
    r.y /= l;
    return r;
}

Point operator + (const Point& p0, const Point& p1) {
    Point r = p0;
    return r += p1;
}

Point operator - (const Point& p0, const Point& p1) {
    Point r = p0;
    return r -= p1;
}

Point operator - (const Point& p) {
    return Point{-p.x, -p.y};
}

Point operator * (const Point& p, const ld& l) {
    Point r = p;
    return r *= l;
}

Point operator / (const Point& p, const ld& l) {
    Point r = p;
    return r /= l;
}

bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool operator == (const Point& a, const Point& b) {
    return eql(a.x, b.x) && eql(a.y, b.y);
}

bool operator == (const Segment& a, const Segment& b) {
    return a.a == b.a && a.b == b.b;
}

bool operator == (const Line& a, const Line& b) {
    return eql(a.a, b.a) && eql(a.b, b.b) && eql(a.c, b.c);
}

bool operator == (const Circle& a, const Circle& b) {
    return a.p == b.p && eql(a.r, b.r);
}

ld dist(const Point& p0, const Point& p1) {
    return (p1 - p0).length();
}

ld dist(const Segment& sg, const Point& pt) {
    Point x = sg.toLine().projection(pt);
    if (sg.inBox(x)) {
        return dist(x, pt);
    }
    return min(dist(sg.a, pt), dist(sg.b, pt));
}

bool Point::null() const {
    return std::isnan(x) || std::isnan(y);
}

ld Point::sq() const {
    return sqr(x) + sqr(y);
}

ld Point::length() const {
    return sqrt(sq());
}

Point Point::rotate90() const {
    return Point{-y, x};
}

ld Point::scalar(const Point& p) const {
    return x * p.x + y * p.y;
}

ld Point::vect(const Point& p) const {
    return p.x * y - p.y * x;
}

int Point::relationTo(const Point& p) const {
    return sgn(vect(p));
}

Line Segment::toLine() const {
    return Line(this->a, this->b);
}

bool Segment::inBox(const Point& p) const {
    return inside(a.x, b.x, p.x) && inside(a.y, b.y, p.y);
}

int Segment::relationTo(const Point& p) const {
    return (b - a).relationTo(p - a);
}

Line::Line(const Point& p0, const Point& p1): Line((p1 - p0).rotate90(), 0) {
    c -= calc(p0);
}

Point Line::norm() const {
    return Point{a, b};
}

Point Line::direction() const {
    return -norm().rotate90();
}

ld Line::sq() const {
    return norm().sq();
}

ld Line::length() const {
    return sqrt(sq());
}

Point Line::projection(const Point& p) const {
    ld t = calc(p);
    return Point{p.x, p.y} - norm() * t;
}

ld Line::calc(const Point& p) const {
    return a * p.x + b * p.y + c;
}

Line Line::rotate90() const {
    Point r9 = norm().rotate90();
    return Line{r9.x, r9.y, 0};
}

Line Line::shiftedTo(const Point& p) const {
    return Line{a, b, c - calc(p)};
}

Line Line::shiftedOn(const Point& p) const {
    return Line{a, b, c - norm().scalar(p)};
}

Point Line::anyPoint() const {
    return -norm() * c;
}

Line directionLine(const Point& from, const Point& dir) {
    return Line{from, from + dir};
}

array<Point, 2> intersect(const Circle& c, const Line& l) {
    array<Point, 2> res;
    Point p = l.projection(c.p);
    ld h = sqr(c.r) - (c.p - p).sq();
    if (h < -EPS) return res;
    if (h < EPS) h = 0;
    h = sqrt(h);
    Point d9 = l.norm().rotate90();
    res[0] = p + d9 * h;
    res[1] = p - d9 * h;
    return res;
}

array<Point, 2> intersect(const Circle& a, const Circle& b) {
    if (a.p == b.p) return {{}};
    Point p = b.p - a.p;
    auto res = intersect(a, Line(p * (-2), p.sq() + sqr(a.r) - sqr(b.r)).shiftedOn(a.p));
    return res;
}

Point intersect(const Line& a, const Line& b) {
    ld v = b.norm().vect(a.norm());
    if (eql(v, 0)) return Point{};
    return Point{a.b * b.c - b.b * a.c, b.a * a.c - a.a * b.c} / v;
}

vector<Point> convexHull(vector<Point> a) {
    if (a.size() == 1) return a;
    sort(a.begin(), a.end());
    Segment line{a[0], a.back()};
    vector<Point> up = {a[0]}, down = {a[0]};
    for (size_t i = 1; i < a.size(); i++) {
        if (line.relationTo(a[i]) <= 0) {
            while (up.size() >= 2 && Segment{up[up.size() - 2], up.back()}.relationTo(a[i]) <= 0)
                up.pop_back();
            up.push_back(a[i]);
        }
        if (line.relationTo(a[i]) >= 0) {
            while (down.size() >= 2 && Segment{down[down.size() - 2], down.back()}.relationTo(a[i]) >= 0)
                down.pop_back();
            down.push_back(a[i]);
        }
    }
    up.insert(up.end(), down.rbegin() + 1, down.rend() - 1);
    if (up.size() == 2 && up[0] == up[1]) up.pop_back();
    return up;
}

ld angle(const Point& p) {
    ld ang = atan2(p.y, p.x);
    if (ang < 0) {
        return ang + 2 * PI;
    }
    return ang;
}

ld angle(ld a, ld b) {
    if (a < b) return b - a;
    return 2 * PI - a + b;
}

ld angle(const Point& a, const Point& b) {
    ld ang = fabs(angle(a) - angle(b));
    return min(ang, 2 * PI - ang);
}

ld degreesOf(ld radians) {
    return radians / PI * 180;
}

ld radiansOf(ld degrees) {
    return degrees / 180 * PI;
}

Point halfplanesIntersection(vector<Line> h) {
    random_shuffle(h.begin(), h.end());
    Point res{0, 0};
    for (size_t i = 0; i < h.size(); i++) {
        const Line& hp = h[i];
        if (hp.calc(res) < EPS) continue;
        res = hp.anyPoint();
        for (size_t j = 0; j < i; j++) {
            if (h[j].calc(res) < EPS) continue;
            Point cross = intersect(h[j], hp);
            if (cross.null()) return Point{};
            res = cross;
        }
        for (size_t j = 0; j < i; j++) {
            if (h[j].calc(res) < EPS) continue;
            return Point{};
        }
    }
    return res;
}