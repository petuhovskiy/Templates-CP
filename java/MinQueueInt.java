package com.petukhovsky.solve.lib;

import java.util.function.BinaryOperator;

/**
 * Created by petuh on 1/30/2016.
 */
public class MinQueueInt {
    private MinStackInt begin;
    private MinStackInt end;

    public MinQueueInt() {
        begin = new MinStackInt();
        end = new MinStackInt();
    }

    public void push(int x) {
        begin.push(x);
    }

    public int pop() {
        if (end.empty()) {
            while (!begin.empty()) {
                end.push(begin.pop());
            }
        }
        return end.pop();
    }

    public int get() {
        if (begin.empty()) return end.get();
        if (end.empty()) return begin.get();
        return Math.min(begin.get(), end.get());
    }
}
