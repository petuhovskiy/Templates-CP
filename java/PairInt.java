package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 2/2/2016.
 */
public class PairInt implements Comparable<PairInt> {

    public int first;
    public int second;

    public PairInt(int first, int second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public int compareTo(PairInt pairInt) {
        if (first > pairInt.first) return 1;
        if (first < pairInt.first) return -1;
        if (second > pairInt.second) return 1;
        return second == pairInt.second ? 0 : -1;
    }

    @Override
    public String toString() {
        return "(" + first + "; " + second + ")";
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof PairInt && compareTo((PairInt) obj) == 0;
    }
}
