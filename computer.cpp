#include "computer.h"
#include <QDebug>


Computer::Computer(QObject* parent):QObject(parent) {

    weights = std::vector<std::vector<int>>(size_of_board, std::vector<int>(size_of_board, 0));

    fieldOfMapItemsComputer = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));
    field = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));
    vectorCordsOfShipsOpponent = std::vector<std::vector<MapItem>>(size_of_board, std::vector<MapItem>(size_of_board, MapItem::EMPTY));

    costs = std::vector<std::vector<int>>(size_of_board, std::vector<int>(size_of_board, 0));

    fieldOfDisplayOfComputer = std::vector<std::vector<int>>(size_of_board, std::vector<int>(size_of_board, 0));

    this->preparingPointsToAttack();
}

std::vector<Cords>  Computer::getCordsOfShipsOfComputer() {
    return cordsOfShipOfComputer;
}

std::vector <std::vector<int>>& Computer::getVectorOfCosts() {
    return costs;
}


std::vector<Ship*>& Computer::getshipsOfComputer() {
    return ShipsOfComputer;
}

std::vector <std::vector<int>>& Computer::getMapOfPlayerComputer() {
    return fieldOfDisplayOfComputer;
}

std::vector <std::vector<MapItem>>& Computer::getFieldItem(){
    return field;
}

std::vector <std::vector<MapItem>>& Computer::getFieldOfComputersItem(){
    return vectorCordsOfShipsOpponent;
}

void Computer::addMapItemToFieldItem(){
    for(auto cords: cordsOfShipOfComputer){
        fieldOfMapItemsComputer[cords.y][cords.x] = MapItem::SHIP;
    }
}

bool Computer::getAccesToStepComputer() {
    return accesToStep;
}

void Computer::deleteShip(Ship* ship) {
    std::vector<Ship*>::iterator iter;
    for (iter = ShipsOfComputer.begin(); iter != ShipsOfComputer.end();) {
        if (*iter == ship) {
            iter = ShipsOfComputer.erase(iter);
            delete ship;
            ship = nullptr;
        }             

        else
            iter++;
    }
}

void Computer::deleteShipFromVectorsShip(int lenght_) {
    std::vector<int>::iterator iter, iter2;

    for (iter = ships_lenght.begin(); iter != ships_lenght.end();) {
        if (*iter == lenght_){
            iter = ships_lenght.erase(iter);
            break;
        }
        else
            iter++;   
    }
}

void Computer::addInItsStrikes(Cords step) {
    itsStrikes.push_back(step);
}

void Computer::preparingPointsToAttack() {
    this->calc_for_shipSize();
    emit send_costs_computer();
}

int Computer::getMaxLengthInVec() {
    
    if(ships_lenght.size() > 1){
    auto result = std::max_element(ships_lenght.begin(), ships_lenght.end(), [](int a, int b){
            return a < b;
        });
    return *result;
    }

    if(!ships_lenght.empty())
        return ships_lenght[0];

    return 0;
}
Cords Computer::maxValueOfCosts() {
    int max = costs[0][0];

    for (int i = 0; i < size_of_board; ++i) {
        for (int j = 0; j < size_of_board; ++j) {
            if (max < costs[i][j]) {
                max = costs[i][j];
            }
        }
    }
    std::vector<Cords> maxVl;
    for (int i = 0; i < size_of_board; ++i) {
        for (int j = 0; j < size_of_board; ++j) {
            if (max == costs[i][j]) {
                maxVl.push_back(Cords(j, i));
            }
        }
    }
    Cords cords = maxVl[random_generate(0, maxVl.size() - 1)];

    return cords;
}

Cords Computer::maxValueOfWeigths() {

    int max = weights[0][0];

    for (int i = 0; i < size_of_board; ++i) {
        for (int j = 0; j < size_of_board; ++j) {
            if (max < weights[i][j]) {
                max = weights[i][j];
            }
        }
    }
    std::vector<Cords> maxVl;
    for (int i = 0; i < size_of_board; ++i) {
        for (int j = 0; j < size_of_board; ++j) {
            if (max == weights[i][j]) {
                maxVl.push_back(Cords(j, i));
            }
        }
    }
    Cords cords = maxVl[random_generate(0, maxVl.size() - 1)];

    return cords;
}

Cords Computer::stepOfCosts() {

    Cords step = maxValueOfCosts();

    while (this->checkItsStrikes(step)) {
        step = maxValueOfCosts();
    }
    return step;
}

Cords Computer::stepOfWeights() {

    Cords step = maxValueOfWeigths();

    while (checkItsStrikes(step)) {
        step = maxValueOfWeigths();
    }
    return step;
}

bool Computer::checkItsStrikes(Cords step) {

    std::vector<Cords>::iterator iter = std::find_if(itsStrikes.begin(), itsStrikes.end(), [=](Cords one) {
        return one.x == step.x && one.y == step.y;
        });
    if (iter == itsStrikes.end())
        return false;
    return true;
}

Status Computer::checkKickOpponent(int x, int y) {
    enemyStrikes.push_back(Cords(x, y));

    for (auto ship : ShipsOfComputer) {

        for (auto cordsOfShip : ship->getCordsOfShip()) {
            if (cordsOfShip.x == x && cordsOfShip.y == y) {
                if (ship->getHealth() > 1) {
                    ship->healthDown();
                    return Status::HURT;
                }
                else {
                    this->deleteShip(ship);
                    return Status::DESTROY;
                }
            }
        }
    }
    return Status::MISSING;
}

bool Computer::emptyShipsVector() {
    return ships_lenght.empty();
}

void Computer::stateProcessing(const Cords step, Status status) {
    this->addInItsStrikes(step);
    this->add(step.x, step.y, status);
    
    this->strategy(step.x, step.y, status);

    this->cleanCostsVector();
    this->calc_for_shipSize();
    emit send_costs_computer();
    emit send_item_computer();
}

void Computer::add(int x, int y, Status status) {
    switch (status) {
        case Status::MISSING:{
            //field[y][x] = MapItem::MISS;
            vectorCordsOfShipsOpponent[y][x] = MapItem::MISS;
            break;
        }
        case Status::HURT:{
            //field[y][x] = MapItem::WRECKED;
            vectorCordsOfShipsOpponent[y][x] = MapItem::WRECKED;
            break;
        }
        case Status::DESTROY:{
            //field[y][x] = MapItem::WRECKED;
            vectorCordsOfShipsOpponent[y][x] = MapItem::WRECKED;
            break;
        }
    }
}

void Computer::cleanCostsVector() {
    for (size_t y = 0; y < size_of_board; ++y) {
        for (size_t x = 0; x < size_of_board; ++x) {
            costs[y][x] = 0;
        }
    }
}

void Computer::calc_for_shipSize() {

    size_t shipSize = this->getMaxLengthInVec();

    for (size_t y = 0; y < size_of_board; ++y) {
        for (size_t x = 0; x < size_of_board; ++x) {
            costs[y][x] = distance_for_direction(x, y, shipSize);
        }
    }
}

size_t Computer::distance_for_direction( int x, int y, int shipSize) {

    size_t distance = 0;
    std::vector<size_t> distances_vec;

    for (int d_y = std::min(y, size_of_board - 1); d_y < std::min(y + shipSize, size_of_board); ++d_y) {
        if (vectorCordsOfShipsOpponent[d_y][x] != MapItem::EMPTY) {
            break;
        }
        distance++;
    }
    distances_vec.push_back(distance);
    distance = 0;

    for (int d_y = std::max(y, 0); d_y >= std::max(y - shipSize + 1, 0); --d_y) {
        if (vectorCordsOfShipsOpponent[d_y][x] != MapItem::EMPTY) {
            break;
        }
        distance++;
    }
    distances_vec.push_back(distance);
    distance = 0;

    for (int d_x = std::min(x, size_of_board - 1); d_x < std::min(x + shipSize, size_of_board); ++d_x) {
        if (vectorCordsOfShipsOpponent[y][d_x] != MapItem::EMPTY) {
            break;
        }
        distance++;
    }
    distances_vec.push_back(distance);
    distance = 0;

    for (int d_x = std::max(x, 0); d_x >= std::max(x - shipSize + 1, 0); --d_x) {
        if (vectorCordsOfShipsOpponent[y][d_x] != MapItem::EMPTY) {
            break;
        }
        distance++;
    }
    distances_vec.push_back(distance);

    std::vector<size_t> costs;
    std::transform(distances_vec.begin(),distances_vec.end(), std::back_inserter(costs), [shipSize](size_t dist) {
        if(shipSize != 1 )
            return  dist == shipSize;
        
        else
            return 1 <= dist;
            });


    return std::accumulate(costs.begin(), costs.end(), 0);
}

void Computer::null_weights(int x, int y) {

	for (int c_y = std::max(y - 1, 0); c_y <= std::min(y + 1, size_of_board - 1); ++c_y) {
		for (int c_x = std::max(x - 1, 0); c_x <= std::min(x + 1, size_of_board - 1); ++c_x) {

			if ((std::abs(x - c_x) <= 1 && std::abs(y - c_y) <= 1) || (std::abs(y - c_y) <= 1 && std::abs(x - c_x) <= 1))
				weights[c_y][c_x] = 0;
		}
	}
}

void Computer::mark_cells_of_environment(int x, int y){

    for (int c_y = std::max(y - 1, 0); c_y <= std::min(y + 1, size_of_board - 1); ++c_y) {
		for (int c_x = std::max(x - 1, 0); c_x <= std::min(x + 1, size_of_board - 1); ++c_x) {

			if ((std::abs(x - c_x) <= 1 && std::abs(y - c_y) <= 1) || (std::abs(y - c_y) <= 1 && std::abs(x - c_x) <= 1))
				if(vectorCordsOfShipsOpponent[c_y][c_x] != MapItem::WRECKED && vectorCordsOfShipsOpponent[c_y][c_x] != MapItem::DESTROYED){
                    vectorCordsOfShipsOpponent[c_y][c_x] = MapItem::SURROUNDING;
                    itsStrikes.push_back(Cords(c_x, c_y));
                }
		}
	}
}

int Computer::reset_weights(int x, int y, Direction direction) {
	int count = 0;

    int shipSize = this->getMaxLengthInVec();

	if (direction == HORIZONTAL) {

		for (int i = x; i <= std::min(x + shipSize, size_of_board - 1); ++i) {
			if (vectorCordsOfShipsOpponent[y][i] != MapItem::WRECKED && vectorCordsOfShipsOpponent[y][i] != MapItem::DESTROYED ) {
				weights[y][i] = 0;
				break;
			}
			count++;
            mark_cells_of_environment(i,y);
            vectorCordsOfShipsOpponent[y][i] = MapItem::DESTROYED;
			null_weights(i, y);
		}
		for (int i = x; i >= std::max(x - shipSize, 0); --i) {
			if (vectorCordsOfShipsOpponent[y][i] != MapItem::WRECKED && vectorCordsOfShipsOpponent[y][i] != MapItem::DESTROYED ) {
				weights[y][i] = 0;
				break;
			}
			count++;
            mark_cells_of_environment(i,y);
            vectorCordsOfShipsOpponent[y][i] = MapItem::DESTROYED;
			null_weights(i, y);
		}
	}
	else if (direction == VERTICAL) {
		for (int j = y; std::min(y + shipSize, size_of_board - 1); ++j) {
			if (vectorCordsOfShipsOpponent[j][x] != MapItem::WRECKED && vectorCordsOfShipsOpponent[j][x] != MapItem::DESTROYED ) {
				weights[j][x] = 0;
				break;
			}
			count++;
            mark_cells_of_environment(x, j);
            vectorCordsOfShipsOpponent[j][x] = MapItem::DESTROYED;
			null_weights(x, j);
		}
		for (int j = y; j >= std::max(y - shipSize, 0); --j) {
			if (vectorCordsOfShipsOpponent[j][x] != MapItem::WRECKED && vectorCordsOfShipsOpponent[j][x] != MapItem::DESTROYED) {
				weights[j][x] = 0;
				break;
			}
			count++;
            mark_cells_of_environment(x, j);
            vectorCordsOfShipsOpponent[j][x] = MapItem::DESTROYED;
			null_weights(x, j);
		}
	}
	else {
		null_weights(x, y);
		return 1;
	}

	return count - 1;
}

void Computer::strategy(int x, int y, Status status) {

    Direction direction = check_near_ships(x, y);
    int lengthOfKillsShip;

    switch (status) {

        case DESTROY:{

            switch (direction) {

                case HORIZONTAL:{
                    lengthOfKillsShip = reset_weights(x, y, direction);
                    this->deleteShipFromVectorsShip(lengthOfKillsShip);
                    break;
                }

                case VERTICAL:{
                    lengthOfKillsShip = reset_weights(x, y, direction);
                    this->deleteShipFromVectorsShip(lengthOfKillsShip);
                    break;
                }

                default:{
                    null_weights(x, y);
                    mark_cells_of_environment(x, y);
                    vectorCordsOfShipsOpponent[y][x] = MapItem::DESTROYED;
                    lengthOfKillsShip = 1;
                    this->deleteShipFromVectorsShip(lengthOfKillsShip);
                    break;
                }
            }

            break;
        }
            
        case  HURT:
            update_weights(x, y, status);
            break;

        default:
            this->weights[y][x] = 0;
            break;
    }
}

Direction Computer::check_near_ships(int x, int y) {

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

void Computer::update_weights(int x, int y, Status status) {

	weights[y][x] = 0;
	Direction direction = check_near_ships(x, y);

	for (int c_y = std::max(y - 1, 0); c_y <= std::min(y + 1, size_of_board - 1); ++c_y) {
		for (int c_x = std::max(x - 1, 0); c_x <= std::min(x + 1, size_of_board - 1); ++c_x) {

			if ((std::abs(x - c_x) <= 1 && std::abs(x - c_x) != 0 && std::abs(y - c_y) <= 1) ||
				(std::abs(y - c_y) <= 1 && std::abs(y - c_y) != 0 && std::abs(x - c_x) <= 1)) {

				if ((std::abs(x - c_x) <= 1 && std::abs(x - c_x) != 0 && std::abs(y - c_y) == 0) ||
					(std::abs(y - c_y) <= 1 && std::abs(y - c_y) != 0 && std::abs(x - c_x) == 0)) {

					switch (direction){

                        case HORIZONTAL:{
                            if (vectorCordsOfShipsOpponent[c_y][c_x] == MapItem::EMPTY && c_y == y) {
                                weights[c_y][c_x] = 80;
                            }
                            else
                                weights[c_y][c_x] = 0;
                            break;   
                        }

                        case VERTICAL:{
                            if (vectorCordsOfShipsOpponent[c_y][c_x] == MapItem::EMPTY && c_x == x) {
                                weights[c_y][c_x] = 80;
                            }
                            else
                                weights[c_y][c_x] = 0;
                            break;   
                            }

                        default:
                            weights[c_y][c_x] = 80;
                            break;
                    } 
				}
				else {
					weights[c_y][c_x] = 0;
				}
			}
		}
	}
}

void  Computer::shipsSetupOnVector() {

    for (int lenghtOfShip : ships_lenght) {
        Rotate rotate = static_cast<Rotate> (random_generate(0, 1));
        Ship* ship = new Ship(lenghtOfShip, rotate, lenghtOfShip);
        ship->generatedCordsOfShip(cordsOfShipAndNearshipscordOfComputer);
        ship->AddCordsOffComputerShip(cordsOfShipAndNearshipscordOfComputer, fieldOfDisplayOfComputer);
        ShipsOfComputer.push_back(ship);
    }
    this->addMapItemToFieldItem();
    emit send_cords_ships_computer();
}