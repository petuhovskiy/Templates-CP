package com.petukhovsky.solve.lib;

import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Iterator;

public class ListInt implements Iterable<Integer>{
    private int capacity = 2;
    private int[] data = new int[capacity];
    private int size = 0;

    public ListInt() {
    }

    public ListInt(int n) {
        super();
        resize(n);
    }

    public void push(int x) {
        if (size == capacity) grow();
        data[size++] = x;
    }

    public void clear() {
        capacity = 1;
        data = new int[1];
        size = 0;
    }

    public int pop() {
        return data[--size];
    }

    public int get(int x) {
        return data[x];
    }

    private void grow() {
        if (capacity < 2) {
            capacity++;
        } else {
            capacity = size + (size >> 1);
            //capacity = size << 1;
        }
        data = Arrays.copyOf(data, capacity);
    }

    private void grow(int newSize) {
        capacity = newSize;
        data = Arrays.copyOf(data, capacity);
    }

    public void resize(int newSize) {
        if (newSize > capacity) {
            grow(newSize);
        }
        size = newSize;
    }

    public int size() {
        return size;
    }

    public void readIn(FastScanner sc, int n) {
        int lastSize = size;
        resize(size + n);
        for (int i = 0; i < n; i++) {
            data[lastSize + i] = sc.nextInt();
        }
    }

    public void print(PrintWriter pw) {
        for (int i = 0; i < size; i++) {
            pw.print(data[i] + " ");
        }
        pw.println();
    }

    public void sort(int l, int r) {
        Arrays.sort(data, l, r);
    }

    public void sort() {
        sort(0, size);
    }

    public boolean empty() {
        return size == 0;
    }

    public int back() {
        return data[size - 1];
    }

    @Override
    public Iterator<Integer> iterator() {
        return new Iterator<Integer>() {

            int position = 0;

            @Override
            public boolean hasNext() {
                return position < size;
            }

            @Override
            public Integer next() {
                return data[position++];
            }
        };
    }
}