#pragma once
#include "Point.h"

enum class Tetromino {
    I, O, T, S, Z, J, L
};

class Shape {
    static constexpr int SIZE = 4;
    Point shape[SIZE];
    Tetromino type;

    public:
    Shape(Tetromino t,int x, int y);
    void draw();
    void erase();
    void move();
};

