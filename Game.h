#pragma once
#include "Action.h"
#include "PieceSequence.h"
#include "Player.h"
#include "Screen.h"

class Game {
    static constexpr int P1_BOARD_X = 10;
    static constexpr int P2_BOARD_X = 50;
    static constexpr int BOARD_Y = 0;
    static constexpr int TICK_MS = 50;
    static constexpr int GRAVITY_TICKS = 5;

    Screen screen;
    PieceSequence sequence;   // declared before the players, which keep a reference to it
    Player player1;
    Player player2;
    int tick = 0;
    bool gameOver = false;
    bool paused = false;

    void handleInput();
    void updateGravity();
    void deliverGarbage();
    static Action mapKeyP1(char key);
    static Action mapKeyP2(char key);

public:
    enum class Result { Paused, Finished };   // why run() returned
    enum class Winner { Player1, Player2, Tie };

    Game();
    Result run();
    Winner getWinner() const;   // meaningful once run() returned Finished
    int getScore1() const { return player1.getScore(); }
    int getScore2() const { return player2.getScore(); }
    int getLines1() const { return player1.getLinesCleared(); }
    int getLines2() const { return player2.getLinesCleared(); }
};
