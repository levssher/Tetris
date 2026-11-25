#pragma once
#include "Point.h"
#include "Tetromino.h"

class Shape {
public:
    static constexpr int SIZE = 4;

private:
    Point shape[SIZE];
    Tetromino type;

public:
    Shape(Tetromino t, int x, int y);
    void draw();
    void erase();
    void move(Direction dir = Direction::DOWN);
    void rotate(bool clockwise);
    const Point& getPoint(int i) const {
        return shape[i];
    }
};

