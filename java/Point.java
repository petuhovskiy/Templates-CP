package com.petukhovsky.solve.lib;

/**
 * Created by petuh on 2/2/2016.
 */
public class Point {
    double x;
    double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    @Override
    public String toString() {
        return String.format("%.8f %.8f", x, y);
    }
}
