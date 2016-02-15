package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 2/3/2016.
 */
public class IOUtils {
    public static void readInt(FastScanner scanner, int[] arr, int pos, int cnt) {
        while (cnt > 0) {
            cnt--;
            arr[pos++] = scanner.nextInt();
        }
    }

    public static void readInt(FastScanner scanner, int[] arr) {
        readInt(scanner, arr, 0, arr.length);
    }
}
