cmake_minimum_required(VERSION 4.1)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tetris main.cpp Point.cpp Screen.cpp Shape.cpp Board.cpp Player.cpp Game.cpp)
