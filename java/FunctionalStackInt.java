package com.petukhovsky.solve.lib;

import java.util.function.BinaryOperator;

/**
 * Created by petuh on 1/30/2016.
 */
public class FunctionalStackInt {
    private ListInt stack = new ListInt();
    private ListInt function = new ListInt();
    private BinaryOperator<Integer> operator;

    public FunctionalStackInt(BinaryOperator<Integer> operator) {
        this.operator = operator;
    }

    public int pop() {
        if (!stack.empty()) {
            function.pop();
            return stack.pop();
        }
        return Integer.MIN_VALUE;
    }

    public void push(int x) {
        stack.push(x);
        if (function.empty()) function.push(x);
        else function.push(operator.apply(x, function.back()));
    }

    public int get() {
        if (function.empty()) return 0;
        return function.back();
    }

    public boolean empty() {
        return stack.empty();
    }
}
