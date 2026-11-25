#pragma once
#include "Action.h"
#include "Board.h"
#include "Direction.h"
#include "Shape.h"
#include "Tetromino.h"

class Player {
    Board board;
    Shape shape;
    int spawnX;
    int spawnY;
    bool alive = true;
    bool lockedThisTick = false;

    bool tryMove(Direction dir);
    bool tryRotate(bool clockwise);
    void spawnShape();
    static Tetromino randomTetromino();

public:
    Player(int boardX, int boardY);

    void draw();
    void beginTick();
    void handleAction(Action action);
    void stepGravity();
    bool isAlive() const {
        return alive;
    }
};
