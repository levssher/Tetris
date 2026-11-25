#include <cstdlib>
#include <ctime>
#include "Console.h"
#include "Game.h"
#include "Screen.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    init_console();
    clrscr();
    hideCursor();

    Game game;
    game.run();

    gotoxy(0, Screen::MAX_Y);
    cleanup_console();
    return 0;
}
