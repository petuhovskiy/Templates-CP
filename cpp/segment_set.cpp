template <typename T>
struct segset {

    typedef typename set<pair<T, T> >::iterator Itr;

    set<pair<T, T> > s;
    T cnt = 0;

    void erase(Itr it) {
        cnt -= it->S - it->F + 1;
        s.erase(it);
    }

    void insert(T l, T r) {
        s.insert(mp(l, r));
        cnt += r - l + 1;
    }

    void add(T l, T r) {
        if (s.empty()) {
            insert(l, r);
            return;
        }
        Itr q, f = q = s.lower_bound(mp(l, l - 1));
        if (f != s.begin() && (--f)->S >= l - 1) {
            if (f->S >= r) return;
            l = f->F;
            erase(f);
        }
        while (q != s.end() && q->F <= r + 1)
            if (q->S > r) {
                r = q->S;
                erase(q);
                break;
            } else erase(q++);
        insert(l, r);
    }

    void del(T l, T r) {
        if (s.empty()) return;
        Itr q, f = q = s.lower_bound(mp(l, l - 1));
        if (f != s.begin() && (--f)->S >= l) {
            insert(f->F, l - 1);
            if (f->S > r) {
                insert(r + 1, f->S);
                erase(f);
                return;
            }
            erase(f);
        }
        while (q != s.end() && q->F <= r)
            if (r <= q->S) {
                if (r + 1 <= q->S) insert(r + 1, q->S);
                erase(q);
                break;
            } else erase(q++);
    }

    void print() {
        for(Itr i = s.begin(); i != s.end(); i++) {
            cout << "(" << i->F << "; " << i->S << ") ";
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
