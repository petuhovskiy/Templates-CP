package com.petukhovsky.solve.lib;

import java.util.Arrays;

/**
 * Created by petuh on 2/3/2016.
 */
public class MaxIncrementSegtree {
    int n;
    int[] data;
    int[] inc;
    int h;

    public void build(int[] arr) {
        System.arraycopy(arr, 0, data, n, arr.length);
        for (int i = n - 1; i > 0; i--) data[i] = Math.max(data[i << 1], data[i << 1 | 1]);
    }

    public void apply(int p, int value) {
        data[p] += value;
        if (p < n) inc[p] += value;
    }

    public void recalc(int p) {
        while (p > 1) {
            p >>= 1;
            data[p] = Math.max(data[p<<1], data[p<<1|1]) + inc[p];
        }
    }

    public void push(int p) {
        for (int s = h; s > 0; s--) {
            int i = p >> s;
            if (inc[i] != 0) {
                apply(i<<1, inc[i]);
                apply(i<<1|1, inc[i]);
                inc[i] = 0;
            }
        }
    }

    public void inc(int l, int r, int value) {
        l += n;
        r += n;
        int l0 = l;
        int r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if ((l & 1) != 0) apply(l++, value);
            if ((r & 1) != 0) apply(--r, value);
        }
        recalc(l0);
        recalc(r0 - 1);
    }

    public int query(int l, int r) {
        l += n;
        r += n;
        push(l);
        push(r - 1);
        int res = Integer.MIN_VALUE;
        for (; l < r; l >>= 1, r >>= 1) {
            if ((l & 1) != 0) res = Math.max(res, data[l++]);
            if ((r & 1) != 0) res = Math.max(data[--r], res);
        }
        return res;
    }

    public MaxIncrementSegtree(int n) {
        this.n = n;
        this.h = 0;
        int temp = n;
        while (temp > 0) {
            temp >>= 1;
            this.h++;
        }
        data = new int[n << 1];
        inc = new int[n];
    }
}
