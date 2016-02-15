package com.petukhovsky.solve.lib;

import java.util.Arrays;

/**
 * Created by petuh on 2/2/2016.
 */
public class FenwickInt {

    int[] data;
    int n;

    public FenwickInt(int n) {
        this.n = n;
        this.data = new int[n];
    }

    public void inc(int pos, int delta) {
        for (int i = pos; i < n; i |= i + 1)
            data[i] += delta;
    }

    public int sum(int r) {
        int res = 0;
        for (int i = r; i >= 0; i = (i&(i+1))-1)
            res += data[i];
        return res;
    }

    public int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    public int size() {
        return n;
    }
}
