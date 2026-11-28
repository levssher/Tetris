#include "Player.h"
#include <iomanip>
#include <iostream>
#include "Console.h"

Player::Player(int boardX, int boardY, PieceSequence& seq)
    : board(boardX, boardY),
      sequence(seq),
      nextIndex(1),
      shape(seq.at(0), boardX + 3, boardY),
      spawnX(boardX + 3),
      spawnY(boardY),
      previewX(boardX + 16),
      previewY(boardY + 7),
      statsX(boardX + 22),
      statsY(boardY + 2) {}

int Player::pointsForLines(int n) {
    switch (n) {
        case 1: return 100;
        case 2: return 300;
        case 3: return 500;
        case 4: return 800;
        default: return 0;
    }
}

int Player::garbageForLines(int n) {
    switch (n) {
        case 2: return 1;
        case 3: return 2;
        case 4: return 4;
        default: return 0;
    }
}

void Player::draw() {
    board.draw();
    if (alive) {
        shape.draw();
    }
    drawNextPreview();
    drawStats();
}

// Score on the "Score:" row, lines on the "Lines:" row below it. Padding to a fixed
// width overwrites any longer number that was printed before.
void Player::drawStats() const {
    gotoxy(statsX, statsY);
    std::cout << std::left << std::setw(7) << score;
    gotoxy(statsX, statsY + 1);
    std::cout << std::left << std::setw(7) << linesCleared << std::flush;
}

// Everything that happens when the falling piece settles: lock it, clear full rows,
// add the points, repaint if rows moved, then bring in the next piece.
void Player::lockPiece() {
    board.lock(shape);
    int cleared = board.clearFullLines();
    if (cleared > 0) {
        linesCleared += cleared;
        score += pointsForLines(cleared);
        outgoingGarbage += garbageForLines(cleared);
        board.draw();
    }
    drawStats();
    spawnShape();
}

int Player::takeOutgoingGarbage() {
    int lines = outgoingGarbage;
    outgoingGarbage = 0;
    return lines;
}

void Player::receiveGarbage(int count) {
    if (count <= 0 || !alive) {
        return;
    }

    bool survived = board.addGarbageLines(count);
    if (!survived) {
        alive = false;
        board.draw();
        return;
    }

    // If rising blocks now overlap the falling piece, lift it just enough to clear them.
    int lifted = 0;
    while (!board.canPlace(shape) && lifted < count) {
        bool atTop = false;
        for (int i = 0; i < Shape::SIZE; ++i) {
            if (shape.getPoint(i).getY() <= spawnY) {
                atTop = true;
                break;
            }
        }
        if (atTop) {
            break;
        }
        shape.move(Direction::UP);
        ++lifted;
    }

    if (!board.canPlace(shape)) {
        alive = false;
    }

    board.draw();
    if (alive) {
        shape.draw();
    }
}

// The piece being held is sequence[nextIndex - 1], so the preview is sequence[nextIndex].
// at() creates that piece if this player is the first to need it, which keeps the shared
// sequence exactly one piece ahead of the fastest player.
void Player::drawNextPreview() {
    for (int row = 0; row < 2; ++row) {
        gotoxy(previewX, previewY + row);
        std::cout << "    ";
    }
    Shape preview(sequence.at(nextIndex), previewX, previewY);
    preview.draw();
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
            score += HARD_DROP_POINTS;
            lockedThisTick = true;
            lockPiece();
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
        lockPiece();
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
    shape = Shape(sequence.at(nextIndex++), spawnX, spawnY);
    if (!board.canPlace(shape)) {
        alive = false;
    } else {
        shape.draw();
    }
    drawNextPreview();
}
