#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <vector>
#include <string>
#include "stdlib.h"
#include <cstdlib> // Для работы с функцией system()
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <set>
#include <tuple>

#include "control.h"

#include "ship.h"
#include "gamer.h"
#include "computer.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QDebug>



class Game: public QObject {
    Q_OBJECT


private:

    std::vector<int> ships_lenght{ 4,3,3,2,2,2,1,1,1,1};
    Computer* player_computer;
    Gamer* player_gamer;
    Player player = Player::GAMER;
    Status status_computer;
    Status status_gamer;

    AttackMode mode = AttackMode::SEARCH;
    Cords step_gamer;
    Cords step_computer;
    bool can_step;
    QTimer* timer_game;


public:

    Game(QObject *parent = nullptr, Gamer*gamer_ = nullptr, Computer* computer_ = nullptr);

    void one_step();

signals:
    void acces_step();
    void draw_step_game();
    void can_make_step();
    void game_over();

public slots:
    void getSteps(Cords);
    void game();

};



#endif 