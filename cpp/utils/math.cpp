#include <math.h>

using namespace std;

// defs

using ll = long long;
using ld = long double;

// consts

const ld ldINF = 1e16;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

const ld Nld = numeric_limits<ld>::quiet_NaN();

// basic

bool eq(ld x, ld y) {
    return fabs(x - y) < EPS || (isnan(x) && isnan(y));
}

char signOf(ld x) {
    if (eq(x, 0)) return 0;
    return x > 0 ? 1 : -1;
}

ld sq(ld x) {
    return x * x;
}

// pairs

using pld = pair<ld, ld>;

const pld Npld = make_pair(Nld, Nld);

bool isnan(const pld& p) {
    return isnan(p.first) || isnan(p.second);
}

// other

pld solveSquare(ld a, ld b, ld c) {  // ax^2 + bx + c = 0
    if (eq(a, 0)) {
        return eq(b, 0) ? Npld : pld(-c / b, -c / b);
    }
    ld D = sqrt(b * b - 4 * a * c);
    return pld((-b + D) / (2 * a), (-b - D) / (2 * a));
}

pld intersectProj(ld l1, ld r1, ld l2, ld r2) {  // intersect of two segments
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

