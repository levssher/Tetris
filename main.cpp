#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Console.h"
#include "Screen.h"
#include "Board.h"
#include "Shape.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    init_console();
    clrscr();
    hideCursor();

    Screen s;
    s.draw();

    Board board(10, 0);

    Shape shape(static_cast<Tetromino>(std::rand() % 7), 13, 0);
    shape.draw();

    int tick = 0;
    bool gameOver = false;
    while (!gameOver) {
        bool lockedThisTick = false;

        while (check_kbhit()) {
            char key = static_cast<char>(get_single_char());
            if (key == 'a' || key == 'A') {
                Shape next = shape;
                next.move(Direction::LEFT);
                if (board.canPlace(next)) {
                    shape.erase();
                    shape = next;
                    shape.draw();
                }
            } else if (key == 'd' || key == 'D') {
                Shape next = shape;
                next.move(Direction::RIGHT);
                if (board.canPlace(next)) {
                    shape.erase();
                    shape = next;
                    shape.draw();
                }
            } else if (key == 'w' || key == 'W') {
                Shape next = shape;
                next.rotate(true);
                if (board.canPlace(next)) {
                    shape.erase();
                    shape = next;
                    shape.draw();
                }
            } else if (key == 'q' || key == 'Q') {
                Shape next = shape;
                next.rotate(false);
                if (board.canPlace(next)) {
                    shape.erase();
                    shape = next;
                    shape.draw();
                }
            } else if (key == 's' || key == 'S') {
                for (int step = 0; step < 2; ++step) {
                    Shape next = shape;
                    next.move(Direction::DOWN);
                    if (board.canPlace(next)) {
                        shape.erase();
                        shape = next;
                        shape.draw();
                    } else {
                        break;
                    }
                }
            } else if (key == 'x' || key == 'X') {
                shape.erase();
                while (true) {
                    Shape next = shape;
                    next.move(Direction::DOWN);
                    if (board.canPlace(next)) {
                        shape = next;
                    } else {
                        break;
                    }
                }
                shape.draw();
                board.lock(shape);

                shape = Shape(static_cast<Tetromino>(std::rand() % 7), 13, 0);
                if (!board.canPlace(shape)) {
                    gameOver = true;
                    break;
                }
                shape.draw();
                lockedThisTick = true;
                break;
            }
        }

        if (!gameOver && !lockedThisTick && tick % 5 == 0) {
            Shape next = shape;
            next.move(Direction::DOWN);

            if (board.canPlace(next)) {
                shape.erase();
                shape = next;
                shape.draw();
            } else {
                board.lock(shape);

                shape = Shape(static_cast<Tetromino>(std::rand() % 7), 13, 0);
                if (!board.canPlace(shape)) {
                    gameOver = true;
                } else {
                    shape.draw();
                }
            }
        }

        sleep_ms(50);
        tick++;
    }

    gotoxy(0, Screen::MAX_Y);
    cleanup_console();
    return 0;
}
