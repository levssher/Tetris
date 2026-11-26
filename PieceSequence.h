#pragma once
#include <cstddef>
#include <cstdlib>
#include <vector>
#include "Tetromino.h"

// One shared list of upcoming pieces. Each player keeps its own index into it,
// so both players get the same pieces in the same order, at their own pace.
class PieceSequence {
    std::vector<Tetromino> pieces;

public:
    // Returns the piece at position i. If nobody has reached i yet, a new random
    // piece is generated and remembered, so the next player to ask gets the same one.
    // Callers only ever ask for the position right after the end at most, so one is enough.
    Tetromino at(std::size_t i) {
        if (pieces.size() <= i) {
            pieces.push_back(static_cast<Tetromino>(std::rand() % 7));
        }
        return pieces[i];
    }
};
