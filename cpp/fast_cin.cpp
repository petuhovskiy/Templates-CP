struct IN{} in;
#define cin in

inline bool delim(char &c) {
    return c == ' ' || c == '\n' || c == '\r';
}

template<typename T>
inline IN& operator>>(IN& t, T& a) {
    char buf;
    a = 0;
    while (delim(buf = getchar()));
    if (buf == '-') {
        t >> a;
        a = -a;
        return t;
    }
    while (true){
        a *= 10;
        a += buf - '0';
        if (delim(buf = getchar())) break;
    }
    return t;
}

inline IN& operator>>(IN& t, std::string& s) {
    char buf;
    s.clear();
    while (delim(buf = getchar()));
    do{
        s += buf;
    } while (!delim(buf = getchar()));
    return t;
}

inline IN& operator>>(IN& t, char& c) {
    while (delim(c = getchar()));
    return t;
}
