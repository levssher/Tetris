#pragma once
#include <iostream>
#include "Direction.h"
#include "Console.h"

class Point {
    int x = 1, y = 1;
    int dir_x = 0, dir_y = 1;
    char ch = '*';
    Color color = Color::White;
public:
    Point() {}
    Point(int x1, int y1, int dirx, int diry, char c)
        : Point(x1, y1, dirx, diry, c, Color::White) {}
    Point(int x1, int y1, int dirx, int diry, char c, Color myColor) {
        x = x1;
        y = y1;
        dir_x = dirx;
        dir_y = diry;
        ch = c;
        color = myColor;
    }
    void draw() {
        draw(ch);
    }
    void draw(char c);
    void move();
    void setDirection(Direction dir);
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
};


