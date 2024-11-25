#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "view.h"
#include "gamer.h"
#include "ship.h"
#include "control.h"
#include "computer.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    My_view* view;
};
#endif // WIDGET_H
