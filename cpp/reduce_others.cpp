template<typename T, typename F>
vector<T> reduce_others(vector<T> v, T zero, F f) {
    vector<T> res(v.size(), zero);
    T tmp = zero;
    for (int i = 0; i < v.size(); i++) {
        res[i] = tmp;
        tmp = f(tmp, v[i]);
    }
    tmp = zero;
    for (int i = (int) v.size() - 1; i >= 0; i--) {
        res[i] = f(res[i], tmp);
        tmp = f(tmp, v[i]);
    }
    return res;
}