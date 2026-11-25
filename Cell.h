#pragma once
#include "Console.h"
static constexpr char EMPTY_CHAR = ' ';

class Cell {
    char ch = EMPTY_CHAR;
    Color color = Color::White;

public:
    Cell() {
    }

    Cell(char ch1, Color myColor) : ch(ch1), color(myColor) {
    }

    void updateCell(Color col, char c='*') {
        ch = c;
        color = col;
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
