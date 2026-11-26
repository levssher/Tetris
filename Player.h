#pragma once
#include "Action.h"
#include "Board.h"
#include "Direction.h"
#include "PieceSequence.h"
#include "Shape.h"
#include "Tetromino.h"

class Player {
    Board board;
    PieceSequence& sequence;   // shared with the other player
    std::size_t nextIndex;     // this player's own position in the sequence
    Shape shape;
    int spawnX;
    int spawnY;
    int previewX;   // top-left of the 4x2 "Next" box interior on screen
    int previewY;
    int statsX;     // where the score and lines numbers are printed on screen
    int statsY;
    int score = 0;
    int linesCleared = 0;
    bool alive = true;
    bool lockedThisTick = false;

    bool tryMove(Direction dir);
    bool tryRotate(bool clockwise);
    void lockPiece();
    void spawnShape();
    void drawNextPreview();
    void drawStats() const;

public:
    static constexpr int HARD_DROP_POINTS = 20;

    // Points for clearing n lines at once: 1 -> 100, 2 -> 300, 3 -> 500, 4 -> 800.
    static int pointsForLines(int n);

    Player(int boardX, int boardY, PieceSequence& seq);

    void draw();
    void beginTick();
    void handleAction(Action action);
    void stepGravity();
    bool isAlive() const {
        return alive;
    }
    int getScore() const {
        return score;
    }
    int getLinesCleared() const {
        return linesCleared;
    }
};
