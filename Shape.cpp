#include "Shape.h"

Shape::Shape(Tetromino t, int x, int y) : type(t) {
    switch (t) {
        case Tetromino::I:
            shape[0] = Point(x,     y, 0, 1, '*', Color::LightAqua);
            shape[1] = Point(x + 1, y, 0, 1, '*', Color::LightAqua);
            shape[2] = Point(x + 2, y, 0, 1, '*', Color::LightAqua);
            shape[3] = Point(x + 3, y, 0, 1, '*', Color::LightAqua);
            break;

        case Tetromino::O:
            shape[0] = Point(x,     y,     0, 1, '*', Color::LightYellow);
            shape[1] = Point(x + 1, y,     0, 1, '*', Color::LightYellow);
            shape[2] = Point(x,     y + 1, 0, 1, '*', Color::LightYellow);
            shape[3] = Point(x + 1, y + 1, 0, 1, '*', Color::LightYellow);
            break;

        case Tetromino::T:
            shape[0] = Point(x,     y,     0, 1, '*', Color::LightPurple);
            shape[1] = Point(x + 1, y,     0, 1, '*', Color::LightPurple);
            shape[2] = Point(x + 2, y,     0, 1, '*', Color::LightPurple);
            shape[3] = Point(x + 1, y + 1, 0, 1, '*', Color::LightPurple);
            break;

        case Tetromino::S:
            shape[0] = Point(x + 1, y,     0, 1, '*', Color::LightGreen);
            shape[1] = Point(x + 1, y + 1, 0, 1, '*', Color::LightGreen);
            shape[2] = Point(x + 2, y,     0, 1, '*', Color::LightGreen);
            shape[3] = Point(x,     y + 1, 0, 1, '*', Color::LightGreen);
            break;

        case Tetromino::Z:
            shape[0] = Point(x,     y,     0, 1, '*', Color::LightRed);
            shape[1] = Point(x + 1, y,     0, 1, '*', Color::LightRed);
            shape[2] = Point(x + 1, y + 1, 0, 1, '*', Color::LightRed);
            shape[3] = Point(x + 2, y + 1, 0, 1, '*', Color::LightRed);
            break;

        case Tetromino::J:
            shape[0] = Point(x,     y,     0, 1, '*', Color::LightBlue);
            shape[1] = Point(x + 1, y + 1, 0, 1, '*', Color::LightBlue);
            shape[2] = Point(x,     y + 1, 0, 1, '*', Color::LightBlue);
            shape[3] = Point(x + 2, y + 1, 0, 1, '*', Color::LightBlue);
            break;

        case Tetromino::L:
            shape[0] = Point(x + 2, y,     0, 1, '*', Color::Yellow);
            shape[1] = Point(x + 1, y + 1, 0, 1, '*', Color::Yellow);
            shape[2] = Point(x,     y + 1, 0, 1, '*', Color::Yellow);
            shape[3] = Point(x + 2, y + 1, 0, 1, '*', Color::Yellow);
            break;
    }
}
void Shape::draw() {
    for (int i = 0; i < SIZE; i++) {
        shape[i].draw();
    }
}

void Shape::erase() {
    for (int i = 0; i < SIZE; i++) {
        shape[i].draw(' ');
    }
}

void Shape::move(Direction dir) {
    for (int i=0;i<SIZE;i++) {
        shape[i].setDirection(dir);
        shape[i].move();
    }

}

void Shape::rotate(bool clockwise) {
    if (type == Tetromino::O) {
        return;
    }

    int px = shape[1].getX();
    int py = shape[1].getY();

    for (int i = 0; i < SIZE; i++) {
        int dx = shape[i].getX() - px;
        int dy = shape[i].getY() - py;

        int newX = clockwise ? (px - dy) : (px + dy);
        int newY = clockwise ? (py + dx) : (py - dx);

        shape[i].setPosition(newX, newY);
    }
}
