#include "game.h"
#include "ship.h"
#include "control.h"

Game::Game(QObject* parent, My_view* view, Gamer* gamer, Computer* computer) : 
    QObject(parent), view_(view), gamer_(gamer), computer_(computer){
    
    player = Player::GAMER;
    mode = AttackMode::SEARCH;
    connect(this, &Game::draw_step_game, view_, &My_view::draw_games_steps);
    connect(this, &Game::game_over, view_, &My_view::game_over);

    connect(computer_, &Computer::send_costs_computer, view_, &My_view::reload_all_weights_of_computer);
    connect(computer_, &Computer::send_item_computer, view_, &My_view::reload_all_fields_item_of_computer);

    connect(gamer_, &Gamer::send_all_objects, view_, &My_view::reload_all_objects_gamer);
    connect(gamer_, &Gamer::emit_point_start, view_, &My_view::draw_cords_for_attack);
    connect(computer_, &Computer::send_cords_ships_computer, view_, &My_view::reload_all_objects_computer);
    connect(gamer_, &Gamer::could_steps, this, &Game::getSteps);  
    connect(this, SIGNAL(acces_step()), this, SLOT(game()));

    computer_->shipsSetupOnVector();
}

void Game::getSteps(Cords step_){
    step_gamer = step_;
    emit acces_step();
}

void Game::game() {

    switch (player) {

        case Player::GAMER: {
            
            status_gamer = computer_->checkKickOpponent(step_gamer.x_, step_gamer.y_);

            switch (status_gamer){
                case Status::DESTROY:{
                    gamer_->getLenghtOfDestroyShipAndDeleteShipFromVector(step_gamer.x_, step_gamer.y_);
                    break;
                }
                case Status::MISSING:{
                    player = Player::COMPUTER;
                    break;
                }
            }
            
            if (gamer_->emptyShipsVector()){
                    emit game_over();
                    break;
            }

            gamer_->stateProcessing(step_gamer, status_gamer);
            emit draw_step_game();

            if(status_gamer != Status::MISSING){
                emit can_make_step();
            }
            else{
                emit acces_step();
            }
            break;
        }

        case Player::COMPUTER: {

            switch (mode) {

                case AttackMode::SEARCH: {

                    step_computer = computer_->stepOfCosts();
                    status_computer = gamer_->checkKickOpponent(step_computer.x_, step_computer.y_);

                    switch (status_computer)
                    {
                    case Status::HURT:
                        mode = FINISHING;
                        break;

                    case Status::DESTROY:
                        mode = SEARCH;
                        break;

                    case Status::MISSING:
                        player = Player::GAMER;
                        break;
                    }
                    break;
                }

                case AttackMode::FINISHING: {

                    step_computer = computer_->stepOfWeights();
                    status_computer = gamer_->checkKickOpponent(step_computer.x_, step_computer.y_);
                    
                    switch (status_computer){
                        case Status::HURT:
                            mode = FINISHING;;
                            break;

                        case Status::DESTROY:
                            mode = SEARCH;
                            break;

                        case Status::MISSING:
                            player = Player::GAMER;
                            break;
                        }
                        break;
                }
            }

            if (computer_->emptyShipsVector()){
                    emit game_over();
                    break;
            }
                
            computer_->stateProcessing(step_computer, status_computer);

            emit draw_step_game();

            if(status_computer != Status::MISSING){
                emit acces_step();  
            }
            else{
                emit can_make_step();
            }
            break;
        }
    }
}