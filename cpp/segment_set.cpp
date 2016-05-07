template <typename T>
class segset {

    typedef typename set<pair<T, T> >::iterator Itr;

private:
    set<pair<T, T> > s;

public:
    void add(T l, T r) {
        if (l > r) return;
        Itr fi = s.lower_bound(mp(l, l - 1));
        Itr ir = fi;
        bool do_left = false;
        if (fi != s.begin()) {
            fi--;
            do_left = true;
        }
        Itr tmp;
        while (ir != s.end() && ir->F <= r + 1) {
            if (ir->S > r) {
                r = ir->S;
                s.erase(ir);
                break;
            }
            tmp = ir;
            tmp++;
            s.erase(ir);
            ir = tmp;
        }
        if (do_left && fi->S >= l-1) {
            l = fi->F;
            r = max(r, fi->S);
            s.erase(fi);
        }
        s.insert(mp(l, r));
    }

    void del(T l, T r) {
        if (l > r) return;
        Itr fi = s.lower_bound(mp(l, l - 1));
        Itr ir = fi;
        bool do_left = false;
        if (fi != s.begin()) {
            fi--;
            do_left = true;
        }
        Itr tmp;
        while (ir != s.end() && ir->F <= r) {
            if (r <= ir->S) {
                s.insert(mp(r + 1, ir->S));
                s.erase(ir);
                break;
            }
            tmp = ir;
            tmp++;
            s.erase(ir);
            ir = tmp;
        }
        if (do_left && fi->S >= l) {
            s.insert(mp(fi->F, l - 1));
            if (fi->S > r) {
                s.insert(mp(r + 1, fi->S));
            }
            s.erase(fi);
        }
    }

    void print() {
        for(Itr i = s.begin(); i != s.end(); i++) {
            cout << "(" << i->F << "; " << i->S << ") ";
        }
        cout << endl;
    }

    set<pair<T, T> > set() {
        return s;
    };
};