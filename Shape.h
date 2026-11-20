#pragma once
#include "Point.h"

enum class Tetromino {
    I, O, T, S, Z, J, L
};

class Shape {
    static constexpr int SIZE = 4;
    static constexpr int NUM_KEYS = 6;
    Point shape[SIZE];
    char keys[NUM_KEYS];

    public:
    Shape();
};

