#include <bits/stdc++.h>
#include "../utils/vector.cpp"
#include "../utils/math.cpp"

using namespace std;

#define pb push_back
#define mp make_pair
#define S second
#define F first

#include "point.cpp"
#include "line.cpp"
#include "segment.cpp"
#include "circle.cpp"

#include "area.cpp"
#include "pick_theorem.cpp"
#include "angle.cpp"
#include "ray.cpp"
#include "convex_hull.cpp"

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
