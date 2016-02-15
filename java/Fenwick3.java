package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 1/30/2016.
 */
public class Fenwick3 {

    int w;
    int h;
    int d;

    long[][][] data;

    public Fenwick3(int w, int h, int d) {
        this.w = w;
        this.h = h;
        this.d = d;
        data = new long[w][h][d];
    }

    public Fenwick3(long[][][] data) {
        this.data = data;
        this.w = data.length;
        this.h = data[0].length;
        this.d = data[0][0].length;
    }

    public long sum(int x0, int y0, int z0) {
        long res = 0;
        for (int x = x0; x >= 0; x = (x&(x+1))-1)
            for (int y = y0; y >= 0; y = (y&(y+1))-1)
                for (int z = z0; z >= 0; z = (z&(z+1))-1)
                    res += data[x][y][z];
        return res;
    }

    public void inc(int x0, int y0, int z0, int delta) {
        for (int x = x0; x < w; x |= x + 1)
            for (int y = y0; y < h; y |= y + 1)
                for (int z = z0; z < d; z |= z + 1)
                    data[x][y][z] += delta;
    }

    public long sum(int x1, int y1, int z1, int x2, int y2, int z2) {
        long ans = sum(x2, y2, z2);
        if (x1 > 0) ans -= sum(x1 - 1, y2, z2);
        if (y1 > 0) ans -= sum(x2, y1 - 1, z2);
        if (z1 > 0) ans -= sum(x2, y2, z1 - 1);
        if (x1 > 0 && y1 > 0) ans += sum(x1 - 1, y1 - 1, z2);
        if (x1 > 0 && z1 > 0) ans += sum(x1 - 1, y2, z1 - 1);
        if (z1 > 0 && y1 > 0) ans += sum(x2, y1 - 1, z1 - 1);
        if (x1 > 0 && y1 > 0 && z1 > 0) ans -= sum(x1 - 1, y1 - 1, z1 - 1);
        return ans;
    }

}
