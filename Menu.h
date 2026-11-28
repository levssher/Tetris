#pragma once
#include "Game.h"

class Menu {
    Game* game = nullptr;            // null = no game exists

    // ---- private helpers: only the menu itself calls these ----
    void showMainMenu() const;
    void startNewGame();
    void continueGame();
    void showInstructions() const;
    void playCurrentGame();          // runs the game, then pauses or ends it
    void clearScreen() const {
        clrscr();
    }

public:
    Menu() = default;                // needed: the deleted copy operations remove the implicit one
    ~Menu() { // deletes the game, if one still exists
        delete game;
    }

    Menu(const Menu&) = delete;      // copying would cause a double delete
    Menu& operator=(const Menu&) = delete;

    void run();                      // the main menu loop
};

