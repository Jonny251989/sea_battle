#include "gamer.h"


Gamer::Gamer(QObject* parent):QObject(parent) {

    fieldOfMapItem = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));
    vectorCordsOfShipsOpponent = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));

    ship = new Ship();
    timer_gemers_ships_setup = new QTimer();
    this->shipSetup();

    QObject::connect(this, SIGNAL(can_make_step()), this, SLOT(make_one_step()));
}

bool Gamer::getAccesToStepGamer() {
    return next_ship;
}

std::vector<Cords>& Gamer::getCordsOfShipsOfGamer() {
    return cordsOfAllShips;
}

std::vector<Ship*>& Gamer::getshipsOfGamer() {
    return ShipsOfGamer;
}

void Gamer::addInItsStrikes(Cords step) {
    itsStrikes.push_back(step);
}

std::vector<std::vector<MapItem>> Gamer::getFieldMapOfGamer(){
    return vectorCordsOfShipsOpponent;
}

void Gamer::shipSetup(){
    QObject::connect(timer_gemers_ships_setup, SIGNAL(timeout()), this, SLOT(setupGamersShips()));
    timer_gemers_ships_setup->start(100);
}

void Gamer::make_one_step(){
    timer_gemers_ships_computers_attack = new QTimer();
    QObject::connect(timer_gemers_ships_computers_attack, SIGNAL(timeout()), this, SLOT(stepForAttackComputersShips()));
    timer_gemers_ships_computers_attack->start(90);
}

void Gamer::stepForAttackComputersShips(){

    // if(GetAsyncKeyState(VK_LEFT)){
    //             --x;
    //         }
    //     if(GetAsyncKeyState(VK_RIGHT)){
    //             ++x;
    //         }
    //     if(GetAsyncKeyState(VK_UP)){
    //             --y;
    //         }
    //     if(GetAsyncKeyState(VK_DOWN)){
    //             ++y;
    //         }
    //     if(GetAsyncKeyState(VK_RETURN)){

    //         this->emit_point_start(x, y);

    //         if(can_make_step(x, y)){
    //             mode_search_cords_for_attack = false;
    //             timer_gemers_ships_computers_attack->stop();
    //             delete timer_gemers_ships_computers_attack;
    //             emit could_steps(Cords(x,y));
    //             return;
    //         }
    //     }
    //     this->checkBorder();
    //     this->emit_point_start(x, y);
}

void Gamer::checkBorder(){
    if (x > SIZE_FIELD - 1)
        x = 0;

    else if (x < 0)
        x = SIZE_FIELD - 1;

    else if (y > SIZE_FIELD - 1)
        y = 0;

    else if (y < 0)
        y = SIZE_FIELD - 1;
}

void Gamer::setupGamersShips() {
    if(index > SIZE_FIELD - 1){
        next_ship = false;
        this->addMapItemToFieldItem();
        timer_gemers_ships_setup->stop();
        delete timer_gemers_ships_setup;
        this->make_one_step();
        return;
    }

    if(next_ship ){
        
        int lenghtOfShip = ships_lenght[index];

        Rotate rotate = static_cast<Rotate> (random_generate(0, 1));
        ship = new Ship(lenghtOfShip, rotate, lenghtOfShip);
        ship->generatedCordsOfShip(cordsOfShipAndNearshipscord);
        ship->add_temporary_points_of_ship();

        next_ship = false;
    }
    // else{
    //     if(GetAsyncKeyState(VK_LEFT)){
    //         if (ship->check_dif(cordsOfAllShips, -1, 0)) {
    //             ship->change_cords_to_move(-1, 0);
    //         }
    //     }
    //     if(GetAsyncKeyState(VK_RIGHT)){                
    //         if (ship->check_dif(cordsOfAllShips, 1, 0)) {
    //             ship->change_cords_to_move(1, 0);
    //         }
    //     }
    //     if(GetAsyncKeyState(VK_UP)){
    //         if (ship->check_dif(cordsOfAllShips, 0, -1)) {
    //             ship->change_cords_to_move(0, -1);
    //         }
    //     }
    //     if(GetAsyncKeyState(VK_DOWN)){
    //         if (ship->check_dif(cordsOfAllShips, 0, 1)) {
    //             ship->change_cords_to_move(0, 1);
    //         }
    //     }
    //     if(GetAsyncKeyState(VK_SPACE)){
    //         if (ship->check_rotate(cordsOfAllShips)) {
    //             ship->rotate_ship();
    //         }
    //     }

    //     if(GetAsyncKeyState(VK_RETURN)){
    //         if (ship->validation_setting_ship_of_near_cords(cordsOfShipAndNearshipscord)) {
    //             ship->addCordsOfShip(cordsOfAllShips, cordsOfShipAndNearshipscord);
    //             index++;
    //             next_ship = true;
    //             ShipsOfGamer.push_back(ship);
    //         }
    //     }
    // }
    emit send_all_objects(ship);
}

void Gamer::stateProcessing(Cords step, Status status){
    this->add(step.x, step.y, status);
    this->addInItsStrikes(step);
}

bool Gamer::can_make_step(int x, int y){
    if(checkItsStrikes(Cords(x,y))){
        return true;
    }
    return false;
}

bool Gamer::checkItsStrikes(Cords step) {

    std::vector<Cords>::iterator iter = std::find_if(itsStrikes.begin(), itsStrikes.end(), [=](Cords one) {
        return one.x == step.x && one.y == step.y;
        });
        if (iter == itsStrikes.end())
            return true;
    return false;
}

void Gamer::addMapItemToFieldItem(){
    for(auto cords: cordsOfAllShips){
        fieldOfMapItem[cords.y][cords.x] = MapItem::SHIP;
    }
}

void Gamer::add(int x, int y, Status status) {
    switch (status) {
        case Status::MISSING:{
            //fieldOfMapItem[y][x] = MapItem::MISS;
            vectorCordsOfShipsOpponent[y][x] = MapItem::MISS;
            break;
        }
        case Status::HURT:{
            //fieldOfMapItem[y][x] = MapItem::WRECKED;
            vectorCordsOfShipsOpponent[y][x] = MapItem::WRECKED;
            break;
        }
        case Status::DESTROY:{
            //fieldOfMapItem[y][x] = MapItem::DESTROYED;
            vectorCordsOfShipsOpponent[y][x] = MapItem::DESTROYED;
            break;
        }
    }
}

int Gamer::getMaxLengthInVec() {
    auto result = std::max_element(ships_lenght.begin(), ships_lenght.end(), [](int a, int b) {
        return a < b;
        });
    return *result;
}

bool Gamer::emptyShipsVector() {
    return ships_lenght.empty();
}

void Gamer::mark_cells_of_environment(int x, int y){

    for (int c_y = std::max(y - 1, 0); c_y <= std::min(y + 1, size_of_board - 1); ++c_y) {
		for (int c_x = std::max(x - 1, 0); c_x <= std::min(x + 1, size_of_board - 1); ++c_x) {

			if(vectorCordsOfShipsOpponent[c_y][c_x] != MapItem::WRECKED && vectorCordsOfShipsOpponent[c_y][c_x] != MapItem::DESTROYED){
                    vectorCordsOfShipsOpponent[c_y][c_x] = MapItem::SURROUNDING;
                    itsStrikes.push_back(Cords(c_x, c_y));
                }
		}
	}
}

Direction Gamer::check_near_ships(int x, int y){
	for (int c_y = std::max(y - 1, 0); c_y <= std::min(y + 1, size_of_board - 1); ++c_y) {
		for (int c_x = std::max(x - 1, 0); c_x <= std::min(x + 1, size_of_board - 1); ++c_x) {

			if ((std::abs(x - c_x) <= 1 && std::abs(x - c_x) != 0 && std::abs(y - c_y) == 0) ||
				(std::abs(y - c_y) <= 1 && std::abs(y - c_y) != 0 && std::abs(x - c_x) == 0)) {

				if (vectorCordsOfShipsOpponent[c_y][c_x] == MapItem::WRECKED && c_y == y)
					return HORIZONTAL;
				if (vectorCordsOfShipsOpponent[c_y][c_x] == MapItem::WRECKED && c_x == x)
					return VERTICAL;
			}
		}
	}
	return ONE;
}

void Gamer::getLenghtOfDestroyShipAndDeleteShipFromVector(int x, int y) {
    int count = 0;

    vectorCordsOfShipsOpponent[y][x] = MapItem::DESTROYED;

    Direction direction = check_near_ships(x, y);
    int size_of_ship = this->getMaxLengthInVec();

    switch(direction){

        case Direction::HORIZONTAL:{
            for (int i = x; i <= std::min(x + size_of_ship, size_of_board - 1); ++i) {
                if (vectorCordsOfShipsOpponent[y][i] != MapItem::WRECKED && vectorCordsOfShipsOpponent[y][i] != MapItem::DESTROYED ) {
                        break;
                }
                    mark_cells_of_environment(i, y);
                    vectorCordsOfShipsOpponent[y][i] = MapItem::DESTROYED;
                    count++;
            }
            for (int i = x; i >= std::max(x - size_of_ship, 0); --i) {
                if (vectorCordsOfShipsOpponent[y][i] != MapItem::WRECKED && vectorCordsOfShipsOpponent[y][i] != MapItem::DESTROYED ) {
                        break;
                }
                mark_cells_of_environment(i, y);
                vectorCordsOfShipsOpponent[y][i] = MapItem::DESTROYED;
                count++;
            }
            break;
        }

        case Direction::VERTICAL:{
            for (int j = y; std::min(y + size_of_ship, size_of_board - 1); ++j) {
                if (vectorCordsOfShipsOpponent[j][x] != MapItem::WRECKED && vectorCordsOfShipsOpponent[j][x] != MapItem::DESTROYED ) {
                    break;
                }
                mark_cells_of_environment(x, j);
                vectorCordsOfShipsOpponent[j][x] = MapItem::DESTROYED;
                count++;
            }
            for (int j = y; j >= std::max(y - size_of_ship, 0); --j) {
                if (vectorCordsOfShipsOpponent[j][x] != MapItem::WRECKED && vectorCordsOfShipsOpponent[j][x] != MapItem::DESTROYED ) {
                    break;
                }
                mark_cells_of_environment(x, j);
                vectorCordsOfShipsOpponent[j][x] = MapItem::DESTROYED;
                count++;
            }
            break;
        }

        case Direction::ONE:{
            this->deleteShipFromVectorsShip(1);
            mark_cells_of_environment(x, y);
            return;
        }
    }

    this->deleteShipFromVectorsShip(count - 1);
}

void Gamer::deleteShipFromVectorsShip(int lenght_) {
    std::vector<int>::iterator iter;
    for (iter = ships_lenght.begin(); iter != ships_lenght.end();) {
        if (*iter == lenght_){
            iter = ships_lenght.erase(iter);
            return;
        }
        else
            iter++;
    }
}

Status Gamer::checkKickOpponent(int x, int y) {
    enemyStrikes.push_back(Cords(x, y));

    for (auto& ship : ShipsOfGamer) {
        for (auto cordsOfShip : ship->getCordsOfShip()) {
            if (cordsOfShip.x == x && cordsOfShip.y == y) {
                if (ship->getHealth() > 1) {
                    ship->healthDown();
                    return Status::HURT;
                }
                else {
                    return Status::DESTROY;
                }
                    
            }
        }
    }
    return Status::MISSING;
}
