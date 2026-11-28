#include "Console.h"
#include "Screen.h"
#include "Colors.h"

void Screen::draw() const {
     Colors::apply(Color::Green);
    for (int i = 0; i < MAX_Y; ++i) {
        gotoxy(0, i);
        std::cout << screen[i] << std::flush;
    }
    reset_color();
}
