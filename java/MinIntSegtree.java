package com.petukhovsky.solve.lib;

import java.util.Arrays;

/**
 * Created by petuh on 1/30/2016.
 */
public class MinIntSegtree {
    int n;
    int[] data;

    public void build(int[] arr) {
        System.arraycopy(arr, 0, data, n, arr.length);
        for (int i = n - 1; i > 0; i--) data[i] = Math.min(data[i << 1], data[i << 1 | 1]);
    }

    public void modify(int node, int value) {
        for (data[node += n] = value; node > 1; node >>= 1) data[node >> 1] = Math.min(data[node], data[node ^ 1]);
    }

    public int query(int l, int r) {
        if (l > r) {
            int d = l;
            l = r;
            r = d;
        }
        l--;
        int res = Integer.MAX_VALUE;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if ((l & 1) != 0) res = Math.min(res, data[l++]);
            if ((r & 1) != 0) res = Math.min(data[--r], res);
        }
        return res;
    }

    public MinIntSegtree(int n) {
        this.n = n;
        data = new int[n << 1];
    }
}
