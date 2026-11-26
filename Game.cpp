#include "Game.h"
#include "Console.h"

Game::Game()
    : player1(P1_BOARD_X, BOARD_Y, sequence),
      player2(P2_BOARD_X, BOARD_Y, sequence) {}

void Game::run() {
    screen.draw();
    player1.draw();
    player2.draw();

    while (!gameOver) {
        player1.beginTick();
        player2.beginTick();

        handleInput();
        if (gameOver || !player1.isAlive() || !player2.isAlive()) {
            gameOver = true;
            break;
        }

        if (tick % GRAVITY_TICKS == 0) {
            updateGravity();
            if (!player1.isAlive() || !player2.isAlive()) {
                gameOver = true;
                break;
            }
        }

        sleep_ms(TICK_MS);
        tick++;
    }
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
            gameOver = true;
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
