#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QList>
#include <QDebug>

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QObject>
#include <QColor>
#include <QMessageBox>

#include "gamer.h"
#include "ship.h"
#include "control.h"
#include "computer.h"
#include "game.h"


class My_view : public QGraphicsView
{
    Q_OBJECT

private:

    QGraphicsScene* scene;
    std::list<QGraphicsItem*> m_moved_items;
    std::list<QGraphicsItem*> m_moved_items_computer;
    std::list<QGraphicsItem*> m_moved_weights_of_computer;
    std::list<QGraphicsItem*> m_moved_fields_item_of_computer;
    std::list<QGraphicsItem*> m_moved_points_attack;
    std::list<QGraphicsItem*> m_moved_games_item;


    Gamer* gamer;
    Computer* computer;

    QTimer* timerBeginGame;

    Game* game;

    int width;
    int heigth;

public:
    My_view(QWidget *parent = nullptr);
    void draw_field();

    void set_all_collors();


    ~My_view();

signals:
    void stop();

public slots:
    void reload_all_objects_gamer(Ship*ship);
    void reload_all_objects_computer();
    void reload_all_weights_of_computer();
    void reload_all_fields_item_of_computer();
    void draw_cords_for_attack(int, int);
    void game_over();

    void draw_games_steps();



};
#endif // VIEW_H
