#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <string>
#undef min
#undef max
#include "stdlib.h"
#include <cstdlib> // Для работы с функцией system()
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <set>
#include <tuple>
#include "control.h"


class Ship {


private:

    int x;
    int y;
    int lenght;
    Rotate rotate;
    int health;

    std::vector<Cords> cordsOfShip;
    std::vector<Cords> cordsOfShipAndNearOfShipCords;

public:

    Ship(int m_lenght = 0 , Rotate m_rotate = Rotate::Horizontal, int health_ = 0, size_t x_ = 0, size_t y_ = 0);

    int getX();
    int getY();
    int getLenght();
    int getHealth();
    Rotate getRotate();
    void healthDown();
    std::vector<Cords> getCordsOfShip();
    Ship* getAdressOfShip();


    void add_temporary_points_of_ship();

    void addCordsOfShip( std::vector<Cords>& cordsOfAllShip, std::vector<Cords>& cordsOfShipAndNearshipscord);

    void addNearCords(std::vector<Cords>& cordsOfShipAndNearshipscord);

    void generatedCordsOfShip(std::vector<Cords>& cordsOfShipAndNearshipscord);

    bool validation_setting_ship_of_near_cords(std::vector<Cords>& cordsOfShipAndNearshipscord);

    bool check_cordsOfShipAndNearshipscord(int x, int y, std::vector<Cords>& cordsOfShipAndNearshipscord);

    bool validationOfCordInVectorOfNearCordsOfShips(std::vector<Cords>& cordsOfShipAndNearshipscord);

    bool bordersCondition();

    bool check_rotate(std::vector<Cords>& cordsOfShipAndNearshipscord);

    void rotate_ship();

    void change_cords_to_move(int dx, int dy);

    bool check_dif(std::vector<Cords>& cordsOfShips, int dx, int dy);

    void AddCordsOffComputerShip(std::vector<Cords>& cordsOfShipAndNearshipscordOfComputer, std::vector <std::vector<int>>& fieldOfDisplay);

};


#endif // MODEL_H