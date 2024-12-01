#include "gamer.h"


Gamer::Gamer(QObject* parent):QObject(parent) {

    fieldOfMapItem = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));
    vectorCordsOfShipsOpponent = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));
    x = 0, y = 0;
}

void Gamer::stepForAttackComputersShips(QKeyEvent* event){
    switch (event->key()) {
        case Qt::Key_Left:
            --x;
            break;
        case Qt::Key_Right:
            ++x;
            break;
        case Qt::Key_Up:
            --y;
            break;
        case Qt::Key_Down:
            ++y;
            break;
        case Qt::Key_Return:{
            if(can_make_step(x, y)) emit could_steps(Cords(x,y));           
            break;
        }
    }
    this->checkBorder();
    this->emit_point_start(x, y);
}

void Gamer::get_key_event(QKeyEvent* event){
    if(is_setup)
        setupGamersShips(event);
    else
        stepForAttackComputersShips(event);
}

void Gamer::setupGamersShips(QKeyEvent* event) {

    if(next_ship ){
        
        int lenghtOfShip = ships_lenght[index];

        Rotate rotate = static_cast<Rotate> (random_generate(0, 1));
        ship = new Ship(lenghtOfShip, rotate, lenghtOfShip);
        ship->generatedCordsOfShip(cordsOfShipAndNearshipscord);
        ship->add_temporary_points_of_ship();

        next_ship = false;
    }
    switch (event->key()) {
        case Qt::Key_Left:{
            if (ship->check_dif(cordsOfAllShips, -1, 0)) {
                ship->change_cords_to_move(-1, 0);
            }
            break;
        }
        case Qt::Key_Right:{
            if (ship->check_dif(cordsOfAllShips, 1, 0)) {
                ship->change_cords_to_move(1, 0);
            }
            break;
        }
        case Qt::Key_Up:{
            if (ship->check_dif(cordsOfAllShips, 0, -1)) {
                ship->change_cords_to_move(0, -1);
            }
            break;
        }
        case Qt::Key_Down:{
            if (ship->check_dif(cordsOfAllShips, 0, 1)) {
                ship->change_cords_to_move(0, 1);
            }
            break;
        }
        case Qt::Key_Space:{
            if (ship->check_rotate(cordsOfAllShips)) {
                ship->rotate_ship();
            }
            break;
        }
        case Qt::Key_Return :{
            if (ship->validation_setting_ship_of_near_cords(cordsOfShipAndNearshipscord)) {
                ship->addCordsOfShip(cordsOfAllShips, cordsOfShipAndNearshipscord);
                index++;
                next_ship = true;
                ShipsOfGamer.push_back(ship);
            }

            if(index > SIZE_FIELD - 1){
                this->addMapItemToFieldItem();
                is_setup = false;
            }           
            break;
        }
    }
emit send_all_objects(ship);
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

void Gamer::stateProcessing(Cords step, Status status){
    this->add(step.x_, step.y_, status);
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
        return one.x_ == step.x_ && one.y_ == step.y_;
        });
        if (iter == itsStrikes.end())
            return true;
    return false;
}

void Gamer::addMapItemToFieldItem(){
    for(auto cords: cordsOfAllShips){
        fieldOfMapItem[cords.y_][cords.x_] = MapItem::SHIP;
    }
}

void Gamer::add(int x, int y, Status status) {
    switch (status) {
        case Status::MISSING:{
            vectorCordsOfShipsOpponent[y][x] = MapItem::MISS;
            break;
        }
        case Status::HURT:{
            vectorCordsOfShipsOpponent[y][x] = MapItem::WRECKED;
            break;
        }
        case Status::DESTROY:{
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
            if (cordsOfShip.x_ == x && cordsOfShip.y_ == y) {
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