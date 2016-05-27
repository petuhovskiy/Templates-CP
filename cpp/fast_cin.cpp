struct IN{} in;

inline bool delim(char &c) {
    return c == ' ' || c == '\n' || c == '\r';
}

inline IN& operator>>(IN& t, int& a) {
    char buf;
    a = 0;
    while (delim(buf = getchar()));
    if (buf == '-') {
        t >> a;
        a = -a;
        return t;
    }
    while (true){
        a = a * 10 + buf - '0';
        if (delim(buf = getchar())) break;
    }
    return t;
}

#define cin in
