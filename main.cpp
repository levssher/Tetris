#include <cstdlib>
#include <ctime>
#include "Console.h"
#include "Menu.h"
#include "Screen.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    init_console();
    clrscr();
    hideCursor();

    Menu menu;
    menu.run();

    gotoxy(0, Screen::MAX_Y);
    cleanup_console();
    return 0;
}
