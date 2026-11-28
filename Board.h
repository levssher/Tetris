#pragma once
#include "Point.h"
#include "Shape.h"
#include "Cell.h"

class Board {
public:
    static constexpr int ROWS = 20;
    static constexpr int COLS = 10;

private:
    int offsetX, offsetY;
    Cell grid[ROWS][COLS];

public:
    Board(int x, int y);
    bool isBlocked(const Point& p) const;
    bool canPlace(const Shape& s) const;
    void lock(const Shape& s);
    void draw() const;
    int clearFullLines();

    // Pushes existing blocks up by `count` rows and inserts `count` garbage lines
    // at the bottom, each with 8 solid blocks and 2 empty gap columns (`gap1`, `gap2`).
    // Returns false if any locked block is pushed above the top boundary (top-out).
    bool addGarbageLines(int count, int gap1, int gap2);

    // Same as above, choosing two distinct random gap columns shared by all added lines.
    bool addGarbageLines(int count);
};


