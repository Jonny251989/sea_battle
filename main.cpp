#include "widget.h"
#include "view.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.setFocus();
    return a.exec();
}
