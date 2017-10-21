namespace pick_theorem {
    ll fpts(const vector<point>& p) {
        point last = p.back();
        ll pts = 0;
        for (size_t i = 0; i < p.size(); i++) {
            ll x = round(fabs(p[i].x - last.x));
            ll y = round(fabs(p[i].y - last.y));
            pts += __gcd(x, y);
            last = p[i];
        }
        return pts;
    }

    ll get(const vector<point>& p) {
        return (round(area::of(p)) * 2 - fpts(p) + 2) / 2;
    }
}