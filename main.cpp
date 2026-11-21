#include <iostream>
#include "Console.h"
#include "Screen.h"
#include "Shape.h"

int main() {
    clrscr();
    hideCursor();

    Screen s;
    s.draw();

    Shape shape(Tetromino::L, 13, 0);
    shape.draw();

    for (int i = 0; i < 18; i++) {
        sleep_ms(300);
        shape.erase();
        shape.move();
        shape.draw();
    }

    gotoxy(0, Screen::MAX_Y);
    return 0;
}
