package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 1/30/2016.
 */
public class FenwickInt3 {

    int w;
    int h;
    int d;

    int[][][] data;

    public FenwickInt3(int w, int h, int d) {
        this.w = w;
        this.h = h;
        this.d = d;
        data = new int[w][h][d];
    }

    public FenwickInt3(int[][][] data) {
        this(data.length, data[0].length, data[0][0].length);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                for (int z = 0; z < d; z++) inc(i, j, z, data[i][j][z]);
            }
        }
    }

    public int sum(int x0, int y0, int z0) {
        int res = 0;
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
        int ans = sum(x2, y2, z2);
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
