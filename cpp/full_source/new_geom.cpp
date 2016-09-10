#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define S second
#define F first

//basic typedef
typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> pld;

const ld ldINF = 1e16;
const ld EPS = 1e-9;
const ld PI = acos(1.0);
const ld Nld = numeric_limits<ld>::quiet_NaN();
const pld Npld = mp(Nld, Nld);

//basic
bool isnan(pld p) {
	return isnan(p.F) || isnan(p.S);
}

bool eq(ld x, ld y) {
	return fabs(x - y) < EPS || (isnan(x) && isnan(y));
}

int fsign(ld x) {
	if (eq(x, 0)) return 0;
	return x > 0 ? 1 : -1;
}

ld sq(ld x) {
	return x * x;
}

pld solveSquare(ld a, ld b, ld c) { //ax^2 + bx + c = 0
	if (eq(a, 0)) {
		return eq(b, 0) ? Npld : pld(-c / b, -c / b);
	}
	ld D = sqrt(b * b - 4 * a * c);
	return pld((-b + D) / (2 * a), (-b - D) / (2 * a));
}

pld intersectProj(ld l1, ld r1, ld l2, ld r2) { //intersect of two segments
	if (l1 > r1) swap(l1, r1);
	if (l2 > r2) swap(l2, r2);
	if (l1 > l2) {
		swap(l1, l2);
		swap(r1, r2);
	}
	return l2 > r1 ? Npld : pld(l2, min(r1, r2));
}

bool within(ld x, ld l, ld r) {
	if (l > r) swap(l, r);
	return x >= l && x <= r;
}
//point
struct point {
	ld x, y;
	point(ld x, ld y): x(x), y(y) {}
	point(): x(Nld), y(Nld) {}

	point operator-(point to) {
		return point(x - to.x, y - to.y);
	}

	point operator+(point to) {
		return point(x + to.x, y + to.y);
	}

	ld operator*(point to) {
		return to.x * y - to.y * x;
	}

	ld operator^(point to) {
		return sqrt(sq(x - to.x) + sq(y - to.y));
	}

	bool operator==(point to) {
		return eq(to.x, x) && eq(to.y, y);
	}

	bool isNull() {
		return isnan(x) || isnan(y);
	}
};

ostream &operator<<(ostream &os, point const &p) {
	return os << p.x << " " << p.y;
}

istream &operator>>(istream &is, point &p) {
	return is >> p.x >> p.y;
}
//line
struct line {
	ld a, b, c;
	line(ld a, ld b, ld c): a(a), b(b), c(c) {}
	line(): a(Nld), b(Nld), c(Nld) {}

	line(point p1, point p2) {
		if (!eq(p1.y, p2.y)) {
			a = 1;
			b = (p1.x - p2.x) / (p2.y - p1.y);
		} else {
			b = 1;
			a = (p2.y - p1.y) / (p1.x - p2.x);
		}
		c = -(a * p1.x + b * p1.y);
	}

	point projection(point p) {
		ld t = -(a * p.x + b * p.y + c) / (sq(a) + sq(b));
		return point(p.x + t * a, p.y + t * b);
	}

	line parallelOf(point p) {
		return line(a, b, -(a * p.x + b * p.y));
	}

	ld findX(ld y) {
		return (-b * y - c) / a;
	}

	ld findY(ld x) {
		return (-a * x - c) / b;
	}

	line rotate90() {
		return line(point(0, 0), point(a, b));
	}

	int relationTo(point p) {
		return fsign(a * p.x + b * p.y + c);
	}

	bool operator==(line to) {
		return eq(a, to.a) && eq(b, to.b) && eq(c, to.c);
	}

	bool isNull() {
		return isnan(a) || isnan(b) || isnan(c);
	}
};

point intersect(line t1, line t2) {
	point r;
	if (eq(t2.a * t1.b - t2.b * t1.a, 0)) return r;
	if (eq(t1.a, 0)) swap(t1, t2);
	r.y = (t1.a * t2.c - t1.c * t2.a) / (t2.a * t1.b - t2.b * t1.a);
	r.x = (t1.b * r.y + t1.c) / (-t1.a);
	return r;
}

istream &operator>>(istream &is, line &l) {
	return is >> l.a >> l.b >> l.c;
}
//segment
struct segment {
	point a, b;
	segment(point a, point b): a(a), b(b) {}
	segment(): a(point()), b(point()) {}

	line toLine() {
		return line(a, b);
	}

	int relationTo(point p) {
		return fsign((b - a) * (p - a));
	}

	bool inBox(point p) {
		return within(p.x, a.x, b.x) && within(p.y, a.y, b.y);
	}

	bool operator==(segment s) {
		return a == s.a && b == s.b;
	}

	bool isNull() {
		return a.isNull() || b.isNull();
	}
};

point intersect(segment s, point p) {
	if (s.inBox(p) && s.relationTo(p) == 0) return p;
	return point();
}

ld operator^(segment s, point p) {
	point x = s.toLine().projection(p);
	if (intersect(s, p).isNull()) return min(p ^ s.a, p ^ s.b);
	return x ^ p;
}

segment intersect(segment x, segment y) {
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

ostream &operator<<(ostream &os, segment const &s) {
	return os << "{(" << s.a << ") (" << s.b << ")}";
}
//circle
struct circle {
	point center;
	ld radius;
	circle(point center, ld radius): center(center), radius(radius) {}
	circle(): center(point()), radius(Nld) {}

	bool operator==(circle c) {
		return center == c.center && eq(radius, c.radius);
	}

	bool isNull() {
		return center.isNull() || isnan(radius);
	}
};

segment intersect(circle c, line l) {
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

vector<point> intersect(circle c, segment s) {
	segment t = intersect(c, s.toLine());
	vector<point> v;
	if (s.inBox(t.a)) v.pb(t.a);
	if (!(t.b == t.a) && s.inBox(t.b)) v.pb(t.b);
	return v;
}

segment intersect (circle c1, circle c2) {
	return intersect(c1, line(-2 * c2.center.x, -2 * c2.center.y,
							 sq(c2.center.x) + sq(c2.center.y) + sq(c1.radius) - sq(c2.radius)));
}

//other
namespace area {
	ld of(point p1, point p2, point p3) {
		return fabs((p2 - p1) * (p3 - p1)) / 2;
	}

	ld of(vector<point> p) {
		ld s = 0;
		point last = p.back();
		for (int i = 0; i < p.size(); i++) {
			s += (p[i].y + last.y) * (p[i].x - last.x);
			last = p[i];
		}
		return fabs(s / 2);
	}
}

namespace pick_theorem {
	ll fpts(vector<point> p) {
		point last = p.back();
		ll pts = 0;
		for (int i = 0; i < p.size(); i++) {
			ll x = round(fabs(p[i].x - last.x));
			ll y = round(fabs(p[i].y - last.y));
			pts += __gcd(x, y);
			last = p[i];
		}
		return pts;
	}

	ll get(vector<point> p) {
		return (round(area::of(p)) * 2 - fpts(p) + 2) / 2;
	}
}

namespace angle {
	ld of(point p) {
		ld a = atan(p.y / p.x);
		if (p.y == 0 && p.x > 0) return 0;
		if (p.x < 0) return PI + a;
		if (p.y > 0) return a;
		return 2 * PI + a;
	}

	ld of(point a, point b) {
		ld x = fabs(of(a) - of(b));
		return min(x, 2 * PI - x);
	}
}

namespace ray {
	bool on(point st, point de, point p) {
		if (de == p) return true;
		de = de - st;
		p = p - st;
		return de * p == 0 && fsign(de.x) == fsign(p.x) && fsign(de.y) == fsign(p.y);
	}

	point shot(point st, point de, ld di) {
		segment s = intersect(circle(st, di), line(st, de));
		return on(st, de, s.a) ? s.a : s.b;
	}
}

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
		for (int i = 1; i < a.size(); i++) {
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

int main() {
	{//circle intersection
		circle c(point(0, 0), 10);
		line l1(point(0, 0), point(1, 0));
		line l2(point(0, 0), point(0, 1));
		segment s1 = intersect(c, l1);
		segment s2 = intersect(c, l2);
		point a1(10, 0), b1(-10, 0);
		point a2(0, -10), b2(0, 10);
		assert(a1 == s1.a || a1 == s1.b);
		assert(b1 == s1.a || b1 == s1.b);
		assert(a2 == s2.a || a2 == s2.b);
		assert(b2 == s2.a || b2 == s2.b);
	}
	return 0;
}
