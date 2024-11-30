#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <experimental/random> 
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <set>
#include <tuple>

extern const int size_of_board;
extern const int SIZE_FIELD;
extern const size_t width;
extern const size_t height;
extern size_t hold;
extern const size_t w_rect;
extern const size_t h_rect;
extern const size_t count_of_ships;

struct Cords {
    int x_, y_;
    Cords(int x_ = -1, int y_ = -1);
};

enum class Rotate {Horizontal, Vertical};
enum Status { HURT, MISSING, DESTROY };
enum Direction { VERTICAL, HORIZONTAL, ONE };
enum MapItem{SHIP, EMPTY, MISS, WRECKED, DESTROYED, SURROUNDING, REFERENCE_POINTS};
enum AttackMode {SEARCH, FINISHING};
enum Player {GAMER, COMPUTER};

int random_generate(int x_lim_min, int x_lim_max);