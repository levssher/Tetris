#pragma once
#include "Console.h"
static constexpr char EMPTY_CHAR = ' ';

class Cell {
    char ch = EMPTY_CHAR;
    Color color = Color::White;

public:
    Cell() = default;

    Cell(char ch1, Color myColor) : ch(ch1), color(myColor) {
    }

    bool isEmpty() const {
        return ch == EMPTY_CHAR;
    }

    char getChar() const {
        return ch;
    }

    Color getColor() const {
        return color;
    }
};
