#pragma once
#include "Point.h"
#include "Shape.h"

class Board {
    static constexpr int ROWS = 20;
    static constexpr int COLS = 10;
    int offsetX, offsetY;
    char grid[ROWS][COLS];

public:
    Board(int x, int y);
    bool isBlocked(const Point& p) const;
    bool canPlace(const Shape& s) const;
    void lock(const Shape& s);
};


