package com.petukhovsky.solve.lib;

public class Matrix {

    int[][] a;
    int n, m;

    public Matrix(int n, int m, int t[]) {
        a = new int[n][m];
        this.n = n;
        this.m = m;
        int it = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = t[it++];
            }
        }
    }

    public Matrix(int n, int m, int t[][]) {
        this.n = n;
        this.m = m;
        a = t;
    }

    public static Matrix oneMatrix(int n) {
        int t[][] = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                t[i][j] = (i == j ? 1 : 0);
            }
        }
        return new Matrix(n, n, t);
    }

    public static Matrix mult(Matrix a, Matrix b, int MOD) {
        int t[][] = new int[a.n][b.m];
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int l = 0; l < a.m; l++) {
                    t[i][j] = (int) ((t[i][j] + (long) a.get(i, l) * b.get(l, j)) % MOD);
                }
            }
        }
        return new Matrix(a.n, b.m, t);
    }

    public static Matrix binpow(Matrix a, long st, int MOD) {
        Matrix ans = oneMatrix(a.n);
        while (st > 0) {
            if ((st & 1) != 0) {
                ans = mult(ans, a, MOD);
            }
            a = mult(a, a, MOD);
            st >>= 1;
        }
        return ans;
    }

    public int get(int x, int y) {
        return a[x][y];
    }
}