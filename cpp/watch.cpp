namespace watch{

    const int SECONDS_IN_DAY = 24 * 60 * 60;
    const int DAYS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int DAYS_LEAP[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool isLeapYear(int year) {
        return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
    }

    int getDaysInYear(int year) {
        return 365 + isLeapYear(year);
    }

    int DAYS_400[400];
    int P_DAYS_400[400];

    auto __precompute_days_400 = [](){
        for (int i = 0; i < 400; i++) {
            P_DAYS_400[i] = DAYS_400[i] = getDaysInYear(i);
            if (i) P_DAYS_400[i] += P_DAYS_400[i - 1];
        }
        return 0;
    }();

    unsigned long long daysInYears(int l, int r) {
        assert(l <= r);
        if (l == r) return 0;
        if (l % 400 == 0) {
            int cnt = r - l;
            int k = cnt / 400;
            unsigned long long res = k * 1ll * P_DAYS_400[399];
            cnt %= 400;
            if (cnt--) res += P_DAYS_400[cnt % 400];
            return res;
        }
        unsigned long long res = daysInYears(l - (l % 400), r);
        int pr = l % 400;
        if (pr--) res -= P_DAYS_400[pr];
        return res;
    }

    void parseMonthDay(int days, int &m, int &d, bool isLeap) {
        const int *arr = (isLeap ? DAYS_LEAP : DAYS);
        m = 0;
        while (days > arr[m]) {
            days -= arr[m++];
        }
        m++;
        d = days;
    }


    struct second{
        int h, m, s;

        bool operator<(const second &to) {
            if (h < to.h) return true;
            if (h > to.h) return false;
            if (m < to.m) return true;
            if (m > to.m) return false;
            return s < to.s;
        }

        bool operator==(const second &to) {
            return h == to.h && s == to.s && m == to.m;
        }

        int toInt() {
            return (h * 60 + m) * 60 + s;
        }

        int operator-(second &t) {
            return toInt() - t.toInt();
        }

        second(int h, int m, int s): h(h), s(s), m(m) {}

        second(int t) {
            s = t % 60;
            t /= 60;
            m = t % 60;
            h = t / 60;
        }
    };

    struct day{
        int y, m, d;
        int w;

        bool isLeap() {
            return isLeapYear(y);
        }

        bool operator<(const day &to) {
            if (y < to.y) return true;
            if (y > to.y) return false;
            if (m < to.m) return true;
            if (m > to.m) return false;
            return d < to.d;
        }

        bool operator==(const day &to) {
            return y == to.y && m == to.m && d == to.d;
        }

        int getDay() {
            const int *arr = (isLeapYear(y) ? DAYS_LEAP : DAYS);
            int res = 0;
            for (int i = 1; i < m; i++) res += arr[i - 1];
            res += d;
            return res;
        }

        unsigned long long operator-(day &t) {
            if ((*this) < t) return -(t - (*this));
            if (y == t.y) return getDay() - t.getDay();
            return daysInYears(t.y + 1, y) + (t.isLeap() ? 366 : 365) - t.getDay() + getDay();
        }

        day(unsigned long long days) {
            w = 3 + (days % 7);
            w %= 7;
            w++;
            days += P_DAYS_400[1970 - 1 - 1600];
            y = 1600;
            y += 400 * (days / P_DAYS_400[399]);
            days %= P_DAYS_400[399];
            int l = 0;
            int r = 399;
            int ans = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (P_DAYS_400[mid] <= days) {
                    ans = mid + 1;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            y += ans;
            if (ans) days -= P_DAYS_400[ans - 1];
            parseMonthDay((int)days + 1, m, d, isLeapYear(y));
        }

        void next() {
            if (++w == 8) w = 1;
            if (m == 12 && d == 31) {
                d = 1;
                m = 1;
                y++;
                return;
            }
            const int *arr = (isLeapYear(y) ? DAYS_LEAP : DAYS);
            if (arr[m - 1] <= d) {
                d = 1;
                m++;
            } else d++;
        }
    };

    struct instant{
        day d;
        second s;

        instant(unsigned long long utc): d(utc / SECONDS_IN_DAY), s(utc % SECONDS_IN_DAY) {}

        unsigned long long operator-(instant &in) {
            day &d2 = d;
            day &d1 = in.d;
            int days = d2 - d1;
            if (days == 0) return s - in.s;
            return SECONDS_IN_DAY * (days - 1ll) + SECONDS_IN_DAY + (s - in.s);
        }
    };

    ostream& operator<<(ostream &out, const day &d) {
        out << d.d << "." << d.m << "." << d.y;
        return out;
    }

    ostream& operator<<(ostream &out, const second &s) {
        out << s.h << ":" << s.m << ":" << s.s;
        return out;
    }

    ostream& operator<<(ostream &out, const instant &ins) {
        out << ins.d << " " << ins.s;
        return out;
    }

}
