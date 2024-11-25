#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#undef min
#undef max
#include "stdlib.h"
#include <cstdlib> // Для работы с функцией system()
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <set>
#include <tuple>

extern const int size_of_board;
extern const int SIZE_FIELD;
extern const int width;
extern const int height;
extern int hold;
extern const int w_rect;
extern const int h_rect;
extern const int count_of_ships;


struct Cords {

    int x;
    int y;
    Cords(int x_ = -1, int y_ = -1);
};


enum class Rotate {Horizontal, Vertical};

enum Status { HURT, MISSING, DESTROY };

enum Direction { VERTICAL, HORIZONTAL, ONE };
enum MapItem{SHIP, EMPTY, MISS, WRECKED, DESTROYED, SURROUNDING, REFERENCE_POINTS};
enum AttackMode {SEARCH, FINISHING};
enum Player {GAMER, COMPUTER};

int random_generate(int x_lim_min, int x_lim_max);




#endif // 