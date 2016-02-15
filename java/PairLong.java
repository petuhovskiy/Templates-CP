package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 2/2/2016.
 */
public class PairLong implements Comparable<PairLong> {

    long f, s;

    PairLong(long f, long s) {
        this.f = f;
        this.s = s;
    }

    PairLong() {
        this(0, 0);
    }

    @Override
    public int compareTo(PairLong pairLong) {
        if (f > pairLong.f) return 1;
        if (f < pairLong.f) return -1;
        if (s > pairLong.s) return 1;
        return s == pairLong.s ? 0 : -1;
    }

    @Override
    public String toString() {
        return "(" + f + "; " + s + ")";
    }
}
