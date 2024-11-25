#include "widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)

{
    this->resize(1150,1150);
    view = new My_view(this);
    
    
}

Widget::~Widget()
{

}

