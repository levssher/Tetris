#include "Menu.h"
#include "Colors.h"
#include <iostream>

using std::cout;

void Menu::showMainMenu() const {
    clearScreen();
    gotoxy(25, 6);
    cout << "TETRIS BATTLE";
    gotoxy(20, 8);
    cout << "(1) Start a new game";
    // (2) only if a game exists
    if (game != nullptr) {
        gotoxy(20, 10);
        cout << "(2) Continue a paused game";
    }
    gotoxy(20, 12);
    cout << "(3) Toggle Color Mode (Colors: " << (Colors::isEnabled() ? "ON" : "OFF") << ")";
    gotoxy(20, 14);
    cout << "(8) Present instructions and keys";
    gotoxy(20, 16);
    cout << "(9) EXIT";
    gotoxy(20, 19);
    cout << "Choose an option: ";
    cout << std::flush;
}

// Deletes any unfinished game and starts a fresh one.
void Menu::startNewGame() {
    delete game;
    game = new Game;
    playCurrentGame();
}

// Does nothing when there is no paused game (option 2 is not even shown then).
void Menu::continueGame() {
    if (game != nullptr) {
        playCurrentGame();
    }
}

// Runs the game until it is paused (ESC) or finished. A paused game is kept so that
// "Continue" resumes the same object; a finished game is deleted.
void Menu::playCurrentGame() {
    clearScreen();
    Game::Result result = game->run();
    if (result == Game::Result::Finished) {
        clearScreen();
        gotoxy(33, 8);
        cout << "GAME OVER";
        gotoxy(30, 10);
        switch (game->getWinner()) {
            case Game::Winner::Player1: cout << "Player 1 WINS!"; break;
            case Game::Winner::Player2: cout << "Player 2 WINS!"; break;
            case Game::Winner::Tie:     cout << "It's a TIE!";   break;
        }
        gotoxy(14, 12);
        cout << "Player 1:  Score " << game->getScore1() << "   Lines cleared " << game->getLines1();
        gotoxy(14, 13);
        cout << "Player 2:  Score " << game->getScore2() << "   Lines cleared " << game->getLines2();
        gotoxy(22, 16);
        cout << "Press any key to return to the menu";
        cout << std::flush;
        while (check_kbhit()) {   // drop keys still queued from the game
            get_single_char();
        }
        get_single_char();
        delete game;
        game = nullptr;
    }
}

void Menu::showInstructions() const {
    clearScreen();
    gotoxy(28, 1);
    cout << "INSTRUCTIONS AND KEYS";

    gotoxy(5, 3);
    cout << "Player 1 (left board)";
    gotoxy(5, 5);
    cout << "LEFT ............ A";
    gotoxy(5, 6);
    cout << "RIGHT ........... D";
    gotoxy(5, 7);
    cout << "ROTATE clockwise  W";
    gotoxy(5, 8);
    cout << "ROTATE counter .. Q";
    gotoxy(5, 9);
    cout << "SOFT DROP (2) ... S";
    gotoxy(5, 10);
    cout << "HARD DROP ....... X";

    gotoxy(45, 3);
    cout << "Player 2 (right board)";
    gotoxy(45, 5);
    cout << "LEFT ............ J";
    gotoxy(45, 6);
    cout << "RIGHT ........... L";
    gotoxy(45, 7);
    cout << "ROTATE clockwise  I";
    gotoxy(45, 8);
    cout << "ROTATE counter .. U";
    gotoxy(45, 9);
    cout << "SOFT DROP (2) ... K";
    gotoxy(45, 10);
    cout << "HARD DROP ....... M";

    gotoxy(5, 13);
    cout << "Score: 1 line = 100, 2 lines = 300, 3 lines = 500, 4 lines = 800";
    gotoxy(5, 14);
    cout << "Hard drop = +20 points (soft drop gives none)";
    gotoxy(5, 15);
    cout << "Garbage sent: 2 lines = 1, 3 lines = 2, 4 lines = 4";
    gotoxy(5, 16);
    cout << "The first player to top out loses. ESC pauses the game.";

    gotoxy(22, 20);
    cout << "Press any key to return to the menu";
    cout << std::flush;
    get_single_char();
}

void Menu::run() {
    bool exitRequested = false;
    while (!exitRequested) {
        showMainMenu();
        char key = static_cast<char>(get_single_char());
        switch (key) {
            case '1':
                startNewGame();
                break;
            case '2':
                continueGame();
                break;
            case '3':
                Colors::toggle();
                break;
            case '8':
                showInstructions();
                break;
            case '9':
                exitRequested = true;
                break;
            default:   // any other key: just redraw the menu
                break;
        }
    }
}
