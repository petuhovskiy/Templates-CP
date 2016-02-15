package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 2/2/2016.
 */
public class ListAlgo {
    public static int[] getTwoMin(ListInt list) {
        int[] result = new int[2];
        result[0] = list.get(0);
        result[1] = list.get(1);
        if (result[0] > result[1]) {
            int d = result[0];
            result[0] = result[1];
            result[1] = d;
        }
        for (int i = 2; i < list.size(); i++) {
            int value = list.get(i);
            if (value < result[1]) {
                result[1] = value;
                if (result[0] > result[1]) {
                    int d = result[0];
                    result[0] = result[1];
                    result[1] = d;
                }
            }
        }
        return result;
    }

    public static int getFirstNotZero(int... arr) {
        for (int i = 0; i < arr.length; i++) if (arr[i] != 0) return arr[i];
        return 0;
    }
}
