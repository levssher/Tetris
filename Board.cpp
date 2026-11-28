#include "Board.h"
#include "Colors.h"

Board::Board(int x, int y) : offsetX(x), offsetY(y) {
}

bool Board::isBlocked(const Point& p) const {
    int col = p.getX() - offsetX;
    int row = p.getY() - offsetY;

    if (col < 0 || col >= COLS || row < 0 || row >= ROWS) {
        return true; // hit wall or floor
    }
    return !grid[row][col].isEmpty() ; // hit a landed piece
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
            grid[row][col].updateCell(s.getPoint (i).getColor());
        }
    }
}

// Repaints every cell of the board, empty ones included (an empty cell prints a
// space), so stale blocks are erased after rows move or the screen is cleared.
void Board::draw() const {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            gotoxy(offsetX + c, offsetY + r);
            Colors::apply(grid[r][c].getColor());
            std::cout << grid[r][c].getChar();
        }
    }
    reset_color();
    std::cout << std::flush;
}

// Removes every full row and drops the rows above it by one. Returns how many
// rows were removed (0-4 for a single locked piece). Does not redraw.
int Board::clearFullLines() {
    int cleared = 0;
    int row = ROWS - 1;
    while (row >= 0) {
        bool full = true;
        for (int c = 0; c < COLS; ++c) {
            if (grid[row][c].isEmpty()) {
                full = false;
                break;
            }
        }
        if (!full) {
            --row;
            continue;
        }
        for (int r = row; r > 0; --r) {
            for (int c = 0; c < COLS; ++c) {
                grid[r][c] = grid[r - 1][c];
            }
        }
        for (int c = 0; c < COLS; ++c) {
            grid[0][c] = Cell();
        }
        ++cleared;
        // No --row here: the row we stand on now holds what used to be above it,
        // and that row may be full too.
    }
    return cleared;
}
