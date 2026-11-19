#include <iostream>

#pragma once
#include "Point.h"

using std::cout, std::endl;

class Screen {
public:
	enum { MAX_X = 80, MAX_Y = 25 };
private:
const char* screen[MAX_Y] = {
	//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	    "         #          #                            #          #                  ", // 0
		"         #          #    Player 1                #          #    Player 2      ", // 1
		"         #          #    Score:                  #          #    Score:        ", // 2
		"         #          #    Lines:                  #          #    Lines:        ", // 3
		"         #          #                            #          #                  ", // 4
		"         #          #    Next:                   #          #    Next:         ", // 5
		"         #          #    +----+                  #          #    +----+        ", // 6
		"         #          #    |    |                  #          #    |    |        ", // 7
		"         #          #    |    |                  #          #    |    |        ", // 8
		"         #          #    +----+                  #          #    +----+        ", // 9
		"         #          #                            #          #                  ", // 10
		"         #          #                            #          #                  ", // 11
		"         #          #                            #          #                  ", // 12
		"         #          #                            #          #                  ", // 13
		"         #          #                            #          #                  ", // 14
		"         #          #                            #          #                  ", // 15
		"         #          #                            #          #                  ", // 16
		"         #          #                            #          #                  ", // 17
		"         #          #                            #          #                  ", // 18
		"         #          #                            #          #                  ", // 19
		"         ############                            ############                  ", // 20
		"                                                                               ", // 21
		"                                TETRIS BATTLE                                  ", // 22
		"                                                                               ", // 23
		"                         Press ESC for Pause / Instructions                    "  // 24
};
	char getCharAt(const Point& p) const {
		return screen[p.getY()][p.getX()];
	}
public:
	void draw() const;
	bool isWall(const Point& p) const {
		return getCharAt(p) == '#';
	}
};