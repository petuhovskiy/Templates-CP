const int AB = 26;
const char OFFSET = 'a';

struct trie{
    struct node{
        int goArr[AB];
        int nextArr[AB];
        int link;
        int p;
        char ch;

        node(int v, char c): p(v), ch(c) {
            fill(goArr, goArr + AB, -1);
            fill(nextArr, nextArr + AB, -1);
            link = -1;
        }

        inline int& go(char c) {
            return goArr[c - OFFSET];
        }

        inline int& next(char c) {
            return nextArr[c - OFFSET];
        }

        void printDebug(ostream &out) {
            out << "{" << endl;
            out << "    link = " << link << "," << endl;
            out << "    p = " << p << "," << endl;
            out << "    ch = " << ch << "," << endl;
            out << "}";
        }
    };

    vector<node> t;

    int addString(string &s) {
        int v = 0;
        for (char c : s) {
            if (t[v].next(c) == -1) {
                t[v].next(c) = t.size();
                t.push_back(node(v, c));
            }
            v = t[v].next(c);
        }
        return v;
    }

    int getLink(int v) {
        if (t[v].link == -1) {
            t[v].link = t[v].p == 0 ? 0 : go(getLink(t[v].p), t[v].ch);
        }
        return t[v].link;
    }

    int go(int v, char c) {
        if (t[v].go(c) == -1) {
            if (t[v].next(c) != -1) {
                t[v].go(c) = t[v].next(c);
            } else {
                t[v].go(c) = v == 0 ? 0 : go(getLink(v), c);
            }
        }
        return t[v].go(c);
    }

    trie() {
        t.push_back(node(0, -1));
    }

    void printDebug(ostream &out = cerr) {
        out << "#########" << " Trie " << "#########" << endl;
        out << "nodesCount = " << t.size() << endl;
        for (int i = 0; i < t.size(); i++) {
            getLink(i);
            out << "node[" << i << "] = ";
            t[i].printDebug(out);
            out << endl;
        }
        out << "#########" << " Trie end " << "#########" << endl;
    }
};
