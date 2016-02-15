package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 2/1/2016.
 */
public class MyMath {
    public static int gcd(int x, int y) {
        while (x > 0) {
            y %= x;
            int d = x;
            x = y;
            y = d;
        }
        return y;
    }

    public static int[] intToArray(int x) {
        int[] arr = new int[10];
        int n = 0;
        if (x == 0) {
            n = 1;
            arr[0] = 0;
        } else {
            while (x > 0) {
                arr[n++] = x % 10;
                x /= 10;
            }
        }
        int[] res = new int[n];
        for (int i = 0; i < n; i++) res[i] = arr[n - 1 - i];
        return res;
    }
}
