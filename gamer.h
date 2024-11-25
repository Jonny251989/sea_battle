#ifndef GAMER_H
#define GAMER_H

#include <iostream>
#include <vector>
#include <string>

#include <iterator>
#include <iomanip>
#include <algorithm>
#include <set>
#include <tuple>
#include <QWidget>

#include <QList>
#include <math.h>
#include<QDebug>
#include <random>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

#include "control.h"
#include "ship.h"


class Gamer: public QObject {
    Q_OBJECT

private:

    QTimer* timer_gemers_ships_setup;
    QTimer* timer_gemers_ships_computers_attack;

    int x;
    int y;

    int index = 0;
    bool next_ship = true;

    bool mode_search_cords_for_attack;

    std::pair<int, int> one_step;

    Ship*ship;

    std::vector<int> ships_lenght{ 4,3,3,2,2,2,1,1,1,1 };
    std::vector<int> mode_of_length{ 4,3,2,};

    std::vector<Ship*> ShipsOfGamer;

    std::vector<Cords> cordsOfShipAndNearshipscord;
    std::vector<Cords> cordsOfAllShips;

    std::vector<Cords> enemyStrikes;
    std::vector<Cords> itsStrikes;

    std::vector<std::vector<MapItem>> vectorCordsOfShipsOpponent;
    std::vector<std::vector<MapItem>> fieldOfMapItem;

public:

    Gamer(QObject *parent = nullptr);

    void mark_cells_of_environment(int,int);

    //bool has_near_cell_ship(int, int);

    std::vector<std::vector<MapItem>> getFieldMapOfGamer();

    bool getAccesToStepGamer();

    int getMaxLengthInVec();
    
    void stateProcessing(Cords step, Status status);

    void add(int x, int y, Status status);

    void addMapItemToFieldItem();

    void shipSetup();

    void addInItsStrikes(Cords step);

    void deleteShipFromVectorsShip(int lenght_);

    bool can_make_step(int x, int y);

    bool checkItsStrikes(Cords step);

    bool emptyShipsVector();

    void getLenghtOfDestroyShipAndDeleteShipFromVector(int x, int y);

    Direction check_near_ships(int, int);

    Status checkKickOpponent(int, int);

    std::vector<Cords>& getCordsOfShipsOfGamer();

    std::vector<Ship*>& getshipsOfGamer();

    std::vector <std::vector<int>>& getMapOfPlayerGamer();

    void add_ship_on_vector(std::vector<Cords> one_ship);

    void addShipsOfGamerShipsMap();

    void checkBorder();

public slots:
    void setupGamersShips();
    void stepForAttackComputersShips();
    void make_one_step();

signals:
    void send_all_objects(Ship* ships);
    void emit_point_start(int, int);
    void start_gamer();
    void can_make_step();
    void could_steps(Cords);

};


#endif