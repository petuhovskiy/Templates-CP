package com.petukhovsky.solve.lib;

import java.util.function.BinaryOperator;

/**
 * Created by petuh on 1/30/2016.
 */
public class FunctionalQueueInt {
    private FunctionalStackInt begin;
    private FunctionalStackInt end;
    private BinaryOperator<Integer> operator;

    public FunctionalQueueInt(BinaryOperator<Integer> operator) {
        this.operator = operator;
        begin = new FunctionalStackInt(operator);
        end = new FunctionalStackInt(operator);
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
        return operator.apply(begin.get(), end.get());
    }
}
