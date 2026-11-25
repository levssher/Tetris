#pragma once
#include "Action.h"
#include "Player.h"
#include "Screen.h"

class Game {
    static constexpr int P1_BOARD_X = 10;
    static constexpr int P2_BOARD_X = 50;
    static constexpr int BOARD_Y = 0;
    static constexpr int TICK_MS = 50;
    static constexpr int GRAVITY_TICKS = 5;

    Screen screen;
    Player player1;
    Player player2;
    int tick = 0;
    bool gameOver = false;

    void handleInput();
    void updateGravity();
    static Action mapKeyP1(char key);
    static Action mapKeyP2(char key);

public:
    Game();
    void run();
};
