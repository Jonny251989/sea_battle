#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <vector>
#include <string>

#include "ranges"
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <ranges>
#include <set>
#include <tuple>
#include <map>
#include <numeric>
#include <functional>
#include <random>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

#include "control.h"
#include "ship.h"


class Computer: public QObject {
    Q_OBJECT

    std::vector<int> ships_lenght{ 4,3,3,2,2,2,1,1,1,1 };
    std::vector<int> mode_of_length{ 4,3,2};

    std::vector<std::vector<Ship*>> mapOfComputerShips;

    std::vector<Ship*> ShipsOfComputer;

    std::vector <std::vector<int>> fieldOfDisplayOfComputer;

    std::vector<Cords> cordsOfShipAndNearshipscord;
    std::vector<Cords> cordsOfAllShips;


    std::vector<Cords> cordsOfShipAndNearshipscordOfComputer;
    std::vector<Cords> cordsOfShipOfComputer;


    int size_of_ship;

    std::vector<std::vector<MapItem>> vectorCordsOfShipsOpponent;
    std::vector<std::vector<int>> weights;

    std::vector<std::vector<MapItem>> field;
    std::vector<std::vector<MapItem>> fieldOfMapItemsComputer;

    std::vector<std::vector<int> > costs;


    std::vector<Cords> enemyStrikes;
    std::vector<Cords> itsStrikes;

    bool accesToStep;

public:

    Computer(QObject *parent = nullptr);

    std::vector <std::vector<MapItem>>& getFieldItem();

    void mark_cells_of_environment(int x, int y);

    bool getAccesToStepComputer();

    void addMapItemToFieldItem();

    void addInItsStrikes(const Cords);

    void stateProcessing(const Cords step, Status status);

    void setupsShipsOnStrategy();

    
    void preparingPointsToAttack();

    Cords maxValueOfWeigths();
    Cords maxValueOfCosts();
    int getMaxLengthInVec();

    bool emptyShipsVector();

    void cleanCostsVector();

    void deleteShip(Ship* ship);
    void deleteShipFromVectorsShip(int);

    Cords stepOfCosts();
    Cords stepOfWeights();

    bool checkItsStrikes(Cords step);

    Status checkKickOpponent(int, int);


    std::vector<Cords> getCordsOfShipsOfComputer();


    std::vector <std::vector<int>>& getVectorOfCosts();

    std::vector<Ship*>& getshipsOfComputer();

    std::vector <std::vector<int>>& getMapOfPlayerComputer();

    std::vector <std::vector<MapItem>>& getFieldOfComputersItem();

    void shipsSetupOnVector();

    void reset_zero_vector();


    void add(int x, int y, Status status);

    void update_weights(int x, int y, Status status);

    int reset_weights(int x, int y, Direction direction);

    void null_weights(int x, int y);


    Direction check_near_ships(int, int);

    void strategy(int, int, Status);

    void calc_for_shipSize();

    size_t distance_for_direction(int row, int column, int size_ship);


signals:
    void send_cords_ships_computer();
    void send_costs_computer();
    void send_item_computer();

};






#endif
