#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent){

    setFocusPolicy(Qt::StrongFocus); 

    gamer_ = new Gamer(this);
    computer_ = new Computer(this);

    view_ = new My_view(this, gamer_, computer_);
    game_ = new Game(this, view_, gamer_, computer_);
    
    connect(this, &Widget::send_key, gamer_, &Gamer::get_key_event);
}

void Widget::keyPressEvent(QKeyEvent* event) {
    emit send_key(event);
}

Widget::~Widget(){

}

