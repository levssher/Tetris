#include "Board.h"

Board::Board(int x, int y) : offsetX(x), offsetY(y) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            grid[r][c] = ' ';
        }
    }
}

bool Board::isBlocked(const Point& p) const {
    int col = p.getX() - offsetX;
    int row = p.getY() - offsetY;

    if (col < 0 || col >= COLS || row < 0 || row >= ROWS) {
        return true; // hit wall or floor
    }
    return grid[row][col] != ' '; // hit a landed piece
}

bool Board::canPlace(const Shape& s) const {
    for (int i = 0; i < Shape::SIZE; ++i) {
        if (isBlocked(s.getPoint(i))) {
            return false;
        }
    }
    return true;
}

void Board::lock(const Shape& s) {
    for (int i = 0; i < Shape::SIZE; ++i) {
        int col = s.getPoint(i).getX() - offsetX;
        int row = s.getPoint(i).getY() - offsetY;
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
            grid[row][col] = '*';
        }
    }
}