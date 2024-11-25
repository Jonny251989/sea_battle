
#include "control.h"

const int size_of_board = 10;
const int SIZE_FIELD = 10;
const int width = 550;
const int height = 550;
int hold = 10;
const int w_rect = 50;
const int h_rect = 50;
const int TOP = 10;
const int count_of_ships = 10;

int random_generate(int x_lim_min, int x_lim_max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(x_lim_min, x_lim_max);

    return dist(gen);
}

Cords::Cords(int x_, int y_) :x(x_), y(y_) {};
   
bool operator < (const Cords& a, const Cords& b) {
    return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}

bool operator > (const Cords& a, const Cords& b) {
    return (a.x > b.x) || ((a.x == b.x) && (a.y > b.y));
}

bool operator ==(const Cords& a, const Cords& b) {
    return (a.x == b.x) && (a.y == b.y);
}