#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include "view.h"
#include "gamer.h"
#include "ship.h"
#include "control.h"
#include "computer.h"
#include "gamer.h"
#include "game.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    My_view* view_;
    Computer* computer_;
    Gamer* gamer_;
    Game* game_;
    size_t x, y;

protected:
   virtual void keyPressEvent(QKeyEvent* event);

signals:
    void send_key(QKeyEvent* event);
};
#endif // WIDGET_H
