#include "Game.h"
#include "Console.h"

Game::Game()
    : player1(P1_BOARD_X, BOARD_Y, sequence),
      player2(P2_BOARD_X, BOARD_Y, sequence) {}

// Runs until the match ends (Finished) or ESC is pressed (Paused). Calling run() again
// on a paused game redraws everything and resumes it.
Game::Result Game::run() {
    paused = false;
    screen.draw();
    player1.draw();
    player2.draw();

    while (!gameOver) {
        player1.beginTick();
        player2.beginTick();

        handleInput();
        if (paused) {
            return Result::Paused;
        }
        if (!gameOver) {
            deliverGarbage();
        }
        if (gameOver || !player1.isAlive() || !player2.isAlive()) {
            gameOver = true;
            break;
        }

        if (tick % GRAVITY_TICKS == 0) {
            updateGravity();
            deliverGarbage();
            if (!player1.isAlive() || !player2.isAlive()) {
                gameOver = true;
                break;
            }
        }

        sleep_ms(TICK_MS);
        tick++;
    }
    return Result::Finished;
}

void Game::handleInput() {
    while (check_kbhit()) {
        char key = static_cast<char>(get_single_char());

        if (key == 27) { // ESC
            if (check_kbhit()) {
                while (check_kbhit()) {
                    get_single_char();
                }
                continue;
            }
            paused = true;
            return;
        }

        Action a1 = mapKeyP1(key);
        if (a1 != Action::NONE) {
            player1.handleAction(a1);
            continue;
        }

        Action a2 = mapKeyP2(key);
        if (a2 != Action::NONE) {
            player2.handleAction(a2);
        }
    }
}

void Game::updateGravity() {
    player1.stepGravity();
    player2.stepGravity();
}

void Game::deliverGarbage() {
    int toP2 = player1.takeOutgoingGarbage();
    int toP1 = player2.takeOutgoingGarbage();
    if (toP2 > 0) {
        player2.receiveGarbage(toP2);
    }
    if (toP1 > 0) {
        player1.receiveGarbage(toP1);
    }
}

Action Game::mapKeyP1(char key) {
    switch (key) {
        case 'a': case 'A': return Action::LEFT;
        case 'd': case 'D': return Action::RIGHT;
        case 'w': case 'W': return Action::ROTATE_CW;
        case 'q': case 'Q': return Action::ROTATE_CCW;
        case 's': case 'S': return Action::SOFT_DROP;
        case 'x': case 'X': return Action::HARD_DROP;
        default: return Action::NONE;
    }
}

Action Game::mapKeyP2(char key) {
    switch (key) {
        case 'j': case 'J': return Action::LEFT;
        case 'l': case 'L': return Action::RIGHT;
        case 'i': case 'I': return Action::ROTATE_CW;
        case 'u': case 'U': return Action::ROTATE_CCW;
        case 'k': case 'K': return Action::SOFT_DROP;
        case 'm': case 'M': return Action::HARD_DROP;
        default: return Action::NONE;
    }
}
