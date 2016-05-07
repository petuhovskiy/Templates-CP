template <typename T>
struct segset {

    typedef typename set<pair<T, T> >::iterator Itr;

    set<pair<T, T> > s;
    T cnt = 0;

    void erase(Itr it) {
        cnt -= it->second - it->first + 1;
        s.erase(it);
    }

    void insert(T l, T r) {
        s.insert(make_pair(l, r));
        cnt += r - l + 1;
    }

    void add(T l, T r) {
        if (s.empty()) {
            insert(l, r);
            return;
        }
        Itr q, f = q = s.lower_bound(make_pair(l, l - 1));
        if (f != s.begin() && (--f)->second >= l - 1) {
            if (f->second >= r) return;
            l = f->first;
            erase(f);
        }
        while (q != s.end() && q->first <= r + 1)
            if (q->second > r) {
                r = q->second;
                erase(q);
                break;
            } else erase(q++);
        insert(l, r);
    }

    void del(T l, T r) {
        if (s.empty()) return;
        Itr q, f = q = s.lower_bound(make_pair(l, l - 1));
        if (f != s.begin() && (--f)->second >= l) {
            insert(f->first, l - 1);
            if (f->second > r) {
                insert(r + 1, f->second);
                erase(f);
                return;
            }
            erase(f);
        }
        while (q != s.end() && q->first <= r)
            if (r <= q->second) {
                if (r + 1 <= q->second) insert(r + 1, q->second);
                erase(q);
                break;
            } else erase(q++);
    }

    void print() {
        for(Itr i = s.begin(); i != s.end(); i++) {
            cout << "(" << i->first << "; " << i->second << ") ";
        }
        cout << endl;
    }

    T length() {
        return cnt;
    }

    int size() {
        return s.size();
    }
};
