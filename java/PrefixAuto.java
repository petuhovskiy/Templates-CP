package com.petukhovsky.solve.lib;

import java.util.Arrays;

/**
 * Created by petuh on 2/7/2016.
 */
public class PrefixAuto {

    String string;
    int[] prefix;
    int[][] go;

    public int go(int x, char c) {
        if (go[x][c - 'a'] == -1) {
            go[x][c - 'a'] = (x == string.length() || string.charAt(x) == c) ? x + 1 : x == 0 ? 0 : go(prefix[x - 1], c);
        }
        return go[x][c - 'a'];
    }

    public PrefixAuto(String string) {
        this.string = string;
        prefix = new int[string.length()];
        go = new int[this.string.length()][26];
        for (int[] arr : go) Arrays.fill(arr, -1);
        for (int i = 1; i < string.length(); i++) {
            prefix[i] = go(prefix[i - 1], string.charAt(i));
        }
    }
}
