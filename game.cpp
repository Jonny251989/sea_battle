#include "game.h"
#include "ship.h"
#include "control.h"


     Game::Game(QObject* parent, Gamer*gamer_, Computer* computer_): QObject(parent), player_gamer(gamer_), player_computer(computer_)  {
        
        player = Player::GAMER;
        mode = AttackMode::SEARCH;

        connect(player_gamer, &Gamer::could_steps, this, &Game::getSteps);  
        connect(this, SIGNAL(acces_step()), this, SLOT(game()));
        //connect(this, &Game::can_make_step, player_gamer, &Gamer::make_one_step);
     }

    void Game::getSteps(Cords step_){
        step_gamer = step_;
        emit acces_step();
     }


     void Game::game() {

        switch (player) {

            case Player::GAMER: {
                

                status_gamer = player_computer->checkKickOpponent(step_gamer.x, step_gamer.y);

                switch (status_gamer){

                    case Status::DESTROY:{
                        player_gamer->getLenghtOfDestroyShipAndDeleteShipFromVector(step_gamer.x, step_gamer.y);
                        break;
                    }
                    case Status::MISSING:{
                        player = Player::COMPUTER;
                        break;
                    }
                }
                
                if (player_gamer->emptyShipsVector()){
                        emit game_over();
                        break;
                }

                player_gamer->stateProcessing(step_gamer, status_gamer);
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

                        step_computer = player_computer->stepOfCosts();
                        status_computer = player_gamer->checkKickOpponent(step_computer.x, step_computer.y);

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

                        step_computer = player_computer->stepOfWeights();
                        status_computer = player_gamer->checkKickOpponent(step_computer.x, step_computer.y);
                        
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

                if (player_computer->emptyShipsVector()){
                        emit game_over();
                        break;
                }
                    
                player_computer->stateProcessing(step_computer, status_computer);

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
     

  
