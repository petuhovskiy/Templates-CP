package com.petukhovsky.solve.lib;

import java.util.ArrayList;

/**
 * Created by petuh on 2/2/2016.
 */

public class Pair<F, S> {
    F first;
    S second;

    Pair(F first, S second) {
        this.first = first;
        this.second = second;
    }

    public int hashCode() {
        int hashFirst = first != null ? first.hashCode() : 0;
        int hashSecond = second != null ? second.hashCode() : 0;

        return (hashFirst + hashSecond) * hashSecond + hashFirst;
    }

    public boolean equals(Object other) {
        if (other instanceof Pair) {
            Pair otherPair = (Pair) other;
            return
                    ((this.first == otherPair.first ||
                            (this.first != null && otherPair.first != null &&
                                    this.first.equals(otherPair.first))) &&
                            (this.second == otherPair.second ||
                                    (this.second != null && otherPair.second != null &&
                                            this.second.equals(otherPair.second))));
        }

        return false;
    }

    public static <F extends Comparable, S extends Comparable> ArrayList<Pair<F, ArrayList<S>>> groupsPairs (ArrayList<Pair<F, S>> pairs) {
        ArrayList<Pair<F, ArrayList<S>>> result = new ArrayList<>();
        pairs.stream().sorted(Pair::compare).forEach(pair -> {
            if (result.isEmpty() || !pair.first.equals(result.get(result.size() - 1).first)) {
                result.add(new Pair<>(pair.first, new ArrayList<>()));
            }
            result.get(result.size() - 1).second.add(pair.second);
        });
        return result;
    }

    public static <F extends Comparable, S extends Comparable> int compare (Pair<F, S> a, Pair<F, S> b) {
        return a.first.compareTo(b.first) != 0 ? a.first.compareTo(b.first) : a.second.compareTo(b.second);
    }
}
