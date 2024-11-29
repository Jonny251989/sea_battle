#include "widget.h"



Widget::Widget(QWidget *parent) : QWidget(parent){
    this->resize(1150,1150);
    this->setFocus();
    gamer_ = new Gamer(this);
    computer_ = new Computer(this);
    computer_-> shipsSetupOnVector();
    game_ = new Game(this, gamer_, computer_);
    view_ = new My_view(this, gamer_, computer_);

    connect(game_, &Game::draw_step_game, view_, &My_view::draw_games_steps);
    connect(game_, &Game::game_over, view_, &My_view::game_over);


    

    connect(computer_, &Computer::send_cords_ships_computer, view_, &My_view::reload_all_objects_computer);
    connect(computer_, &Computer::send_costs_computer, view_, &My_view::reload_all_weights_of_computer);
    connect(computer_, &Computer::send_item_computer, view_, &My_view::reload_all_fields_item_of_computer);

    connect(gamer_, &Gamer::send_all_objects, view_, &My_view::reload_all_objects_gamer);
    connect(gamer_, &Gamer::emit_point_start, view_, &My_view::draw_cords_for_attack);

    connect(this, &Widget::send_key, gamer_, &Gamer::get_key_event);
}

void Widget::keyPressEvent(QKeyEvent* event) {
    emit send_key(event);
}

Widget::~Widget(){

}

