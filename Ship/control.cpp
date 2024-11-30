
#include "control.h"

const int size_of_board = 10;
const int SIZE_FIELD = 10;
const size_t width = 550;
const size_t height = 550;
size_t hold = 10;
const size_t w_rect = 50;
const size_t h_rect = 50;
const size_t TOP = 10;
const size_t count_of_ships = 10;

int random_generate(int x_lim_min, int x_lim_max) {
    return std::experimental::randint(x_lim_min, x_lim_max);
}

Cords::Cords(int x, int y) :x_(x), y_(y) {};
   
bool operator < (const Cords& a, const Cords& b) {
    return (a.x_ < b.x_) || ((a.x_ == b.x_) && (a.y_ < b.y_));
}

bool operator > (const Cords& a, const Cords& b) {
    return (a.x_ > b.x_) || ((a.x_ == b.x_) && (a.y_ > b.y_));
}

bool operator ==(const Cords& a, const Cords& b) {
    return (a.x_ == b.x_) && (a.y_ == b.y_);
}