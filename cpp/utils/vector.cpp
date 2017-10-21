#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& v) {
    bool first = true;
    for (const auto& x : v) {
        if (first) first = false;
        else out << " ";
        out << x;
    }
    return out;
}

template <typename T>
T& backI(std::vector<T>& v, size_t pos) {
    return v[v.size() - 1 - pos];
}
