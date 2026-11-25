#include "Player.h"
#include <cstdlib>

Player::Player(int boardX, int boardY)
    : board(boardX, boardY),
      shape(randomTetromino(), boardX + 3, boardY),
      spawnX(boardX + 3),
      spawnY(boardY) {}

void Player::draw() {
    board.draw();
    if (alive) {
        shape.draw();
    }
}

void Player::beginTick() {
    lockedThisTick = false;
}

void Player::handleAction(Action action) {
    if (!alive || lockedThisTick) {
        return;
    }

    switch (action) {
        case Action::LEFT:
            tryMove(Direction::LEFT);
            break;
        case Action::RIGHT:
            tryMove(Direction::RIGHT);
            break;
        case Action::ROTATE_CW:
            tryRotate(true);
            break;
        case Action::ROTATE_CCW:
            tryRotate(false);
            break;
        case Action::SOFT_DROP:
            for (int step = 0; step < 2; ++step) {
                if (!tryMove(Direction::DOWN)) {
                    break;
                }
            }
            break;
        case Action::HARD_DROP:
            shape.erase();
            while (true) {
                Shape next = shape;
                next.move(Direction::DOWN);
                if (board.canPlace(next)) {
                    shape = next;
                } else {
                    break;
                }
            }
            shape.draw();
            board.lock(shape);
            lockedThisTick = true;
            spawnShape();
            break;
        case Action::NONE:
            break;
    }
}

void Player::stepGravity() {
    if (!alive || lockedThisTick) {
        return;
    }

    if (!tryMove(Direction::DOWN)) {
        board.lock(shape);
        spawnShape();
    }
}

bool Player::tryMove(Direction dir) {
    Shape next = shape;
    next.move(dir);
    if (board.canPlace(next)) {
        shape.erase();
        shape = next;
        shape.draw();
        return true;
    }
    return false;
}

bool Player::tryRotate(bool clockwise) {
    Shape next = shape;
    next.rotate(clockwise);
    if (board.canPlace(next)) {
        shape.erase();
        shape = next;
        shape.draw();
        return true;
    }
    return false;
}

void Player::spawnShape() {
    shape = Shape(randomTetromino(), spawnX, spawnY);
    if (!board.canPlace(shape)) {
        alive = false;
    } else {
        shape.draw();
    }
}

Tetromino Player::randomTetromino() {
    return static_cast<Tetromino>(std::rand() % 7);
}
