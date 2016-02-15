package com.petukhovsky.solve.lib;

import java.util.Arrays;

/**
 * Created by petuh on 2/2/2016.
 */
public class FenwickDouble {

    double[] data;
    int n;

    public FenwickDouble(int n) {
        this.n = n;
        this.data = new double[n];
    }

    public void inc(int pos, double delta) {
        for (int i = pos; i < n; i |= i + 1)
            data[i] += delta;
    }

    public double sum(int r) {
        double res = 0;
        for (int i = r; i >= 0; i = (i&(i+1))-1)
            res += data[i];
        return res;
    }

    public double sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    public int size() {
        return n;
    }
}
