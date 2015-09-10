#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <queue>
#include <stack>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

#define pb push_back
#define mp make_pair
#define S second
#define F first

//basic typedef
typedef long double ld;
typedef pair<ld, ld> pld;
//structs
struct pt{ //point
    ld x, y;
};

struct ln{ //line
    ld a, b, c;
};

struct sg{ //segment
    pt a, b;
};

typedef vector<pt> pl; //polygon

//constructors
pt mpt (ld x, ld y) {
    pt obj;
    obj.x = x;
    obj.y = y;
    return obj;
}

ln mln (ld a, ld b, ld c) {
    ln obj;
    obj.a = a;
    obj.b = b;
    obj.c = c;
    return obj;
}

sg msg (pt a, pt b) {
    sg obj;
    obj.a = a;
    obj.b = b;
    return obj;
}
//operators tricks
ostream &operator<<(ostream &os, pt const &p) {
    return os << p.x << " " << p.y;
}

istream &operator>>(istream &is, pt &p) {
    return is >> p.x >> p.y;
}

istream &operator>>(istream &is, ln &l) {
    return is >> l.a >> l.b >> l.c;
}
//consts
const long double ldINF = 1e+018;
const long double EPS = 1e-009;
const pt Npt = mpt(ldINF, ldINF);
const pld Npld = mp(ldINF, ldINF);
const sg Nsg = msg(Npt, Npt);
//equals
bool eq (ld x, ld y) {
    return fabs(x - y) < EPS;
}

bool eq (ln x, ln y) {
    return eq(x.a, y.a) && eq(x.b, y.b) && eq(x.c, y.c);
}

bool eq (pt x, pt y) {
    return eq(x.x, y.x) && eq(x.y, y.y);
}

bool eq (sg x, sg y) {
    return eq(x.a, y.a) && eq(x.b, y.b);
}
//line algos
ln makeln (pt p1, pt p2) {
    ln t;
    if (!eq(p1.y, p2.y)) {
        t.a = 1;
        t.b = (t.a * (p1.x - p2.x)) / (p2.y - p1.y);
    } else {
        t.b = 1;
        t.a = (t.b * (p2.y - p1.y)) / (p1.x - p2.x);
    }
    t.c = -(t.a * p1.x + t.b * p1.y);
    return t;
}

pt intersect (ln t1, ln t2) {
    pt r;
    if (eq(t2.a * t1.b - t2.b * t1.a, 0)) return Npt;
    if (eq(t1.a, 0)) swap(t1, t2);
    r.y = (t1.a * t2.c - t1.c * t2.a) / (t2.a * t1.b - t2.b * t1.a);
    r.x = (t1.b * r.y + t1.c) / (-t1.a);
    return r;
}

ln moveToPt (ln l, pt p) { //parallel line trough pt
    l.c = -(l.a * p.x + l.b * p.y);
    return l;
}

ld findX (ln t, ld y) {
    return (-t.b * y - t.c) / t.a;
}

ld findY (ln t, ld x) {
    return (-t.a * x - t.c) / t.b;
}

int ptRels (ln l, pt p) {
    ld f = l.a * p.x + l.b * p.y - l.c;
    if (eq(0, f)) return 0;
    if (f > 0) return 1;
    return -1;
}
//Basic algos
pld solveSquare (ld a, ld b, ld c) { //ax^2 + bx + c = 0
    if (eq(a, 0)) {
        if (eq(b, 0)) return Npld;
        pld ans;
        ans.F = ans.S = (-c) / b;
        return ans;
    }
    ld D = sqrt(b * b - 4 * a * c);
    pld ans;
    ans.F = (-b + D) / (2 * a);
    ans.S = (-b - D) / (2 * a);
    return ans;
}

pld segsInsc (ld l1, ld r1, ld l2, ld r2) { //intersect of two segments
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
    }
    if (l2 > r1) return Npld;
    pld ans;
    ans.F = l2;
    ans.S = min(r1, r2);
    return ans;
}

bool into (ld x, ld l, ld r) {
    if (l > r) swap(l, r);
    return x >= l && x <= r;
}

ld dist (pt p1, pt p2) { //Pythagoras
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
//Areas
ld triangleArea (pt p1, pt p2, pt p3) {
    return fabs((p3.x - p2.x) * (p1.y - p2.y) - (p3.y - p2.y) * (p1.x - p2.x)) / 2;
}
//segs algos
ln makeln (sg s) {
    return makeln(s.a, s.b);
}

int ptRels (sg s, pt p) {
    ld f = (p.x - s.a.x) * (s.b.y - s.a.y) - (p.y - s.a.y) * (s.b.x - s.a.x);
    if (eq(f, 0)) return 0;
    if (f > 0) return 1;
    return -1;
}

sg perBis (pt p1, pt p2) { //perpendicular bisector
    swap(p1.x, p2.x);
    return msg(p1, p2);
}

pt intersect (sg s, pt p) {
    if (into(p.x, s.a.x, s.b.x) && into(p.y, s.a.y, s.b.y) && ptRels(s, p) == 0) return p;
    return Npt;
}

sg intersect2 (sg x, sg y) {
    if (eq(x.a, x.b)) {
        if (eq(y.a, y.b))
        if (eq(x, y)) return x;
        else return Nsg;
        pt p = intersect(y, x.a);
        if (eq(p, Npt)) return Nsg;
        return msg(p, p);
    }
    if (eq(y.a, y.b)) {
        swap(x, y);
        pt p = intersect(y, x.a);
        if (eq(p, Npt)) return Nsg;
        return msg(p, p);
    }
    ln l1, l2;
    l1 = makeln(x);
    l2 = makeln(y);
    if (eq(l1, l2)) {
        if (eq(l1.b, 0)) {
            pld f = segsInsc(x.a.y, x.b.y, y.a.y, y.b.y);
            if (f == Npld) return Nsg;
            return msg(mpt(findX(l1, f.F), f.F), mpt(findX(l1, f.S), f.S));
        }
        pld f = segsInsc(x.a.x, x.b.x, y.a.x, y.b.x);
        if (f == Npld) return Nsg;
        return msg(mpt(f.F, findY(l1, f.F)), mpt(f.S, findY(l1, f.S)));
    }
    pt p = intersect(l1, l2);
    if (eq(p, Npt))
        return Nsg;
    if (into(p.x, x.a.x, x.b.x) && into(p.y, x.a.y, x.b.y) && into(p.x, y.a.x, y.b.x) && into(p.y, y.a.y, y.b.y))
        return msg(p, p);
    return Nsg;
}

int main() {
    
    return 0;
}
