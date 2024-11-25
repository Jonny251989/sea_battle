#include "ship.h"


    Ship::Ship(int m_lenght, Rotate m_rotate, int health_, size_t x_, size_t y_):
        x(x_),y(y_), lenght(m_lenght), rotate(m_rotate), health(health_){ }

    int Ship::getX() {
        return x;
    }
    int Ship::getY() {
        return y;
    }
    int Ship::getLenght() {
        return lenght;
    }
    int Ship::getHealth() {
        return health;
    }
    Rotate Ship::getRotate() {
        return rotate;
    }
    std::vector<Cords> Ship::getCordsOfShip() {
        return cordsOfShip;
    }
    Ship* Ship::getAdressOfShip() {
        return this;
    }

    void Ship::healthDown() {
        this->health = health - 1;
    }


    void Ship::add_temporary_points_of_ship() {
        if (rotate == Rotate::Horizontal) {
            for (int i = x; i < x + lenght; ++i) {
                cordsOfShip.push_back(Cords(i, y));
            }
        }
        else {
            for (int j = y; j < y + lenght; ++j) {
                cordsOfShip.push_back(Cords(x, j));
            }
        }
    }

    void Ship::addCordsOfShip( std::vector<Cords>& cordsOfAllShip, std::vector<Cords>& cordsOfShipAndNearshipscord) {

        std::copy(cordsOfShip.begin(), cordsOfShip.end(), std::back_inserter(cordsOfAllShip));
        addNearCords(cordsOfShipAndNearshipscord);
    }

    void Ship::addNearCords(std::vector<Cords>& cordsOfShipAndNearshipscord) {

        for (Cords cord: cordsOfShip) {
            for (int y = std::max(cord.y - 1, 0); y <= std::min(cord.y + 1, size_of_board - 1); ++y) {
                for (int x = std::max(cord.x - 1, 0); x <= std::min(cord.x + 1, size_of_board - 1); ++x) {
                    if(check_cordsOfShipAndNearshipscord(x,y, cordsOfShipAndNearshipscord))
                        cordsOfShipAndNearshipscord.push_back(Cords(x, y));
                }
            }
        }
    }



    void Ship::generatedCordsOfShip(std::vector<Cords>& cordsOfShipAndNearshipscord) {
            do {
                x = random_generate(0, 9);
                y = random_generate(0, 9);

            } while (bordersCondition() || validationOfCordInVectorOfNearCordsOfShips(cordsOfShipAndNearshipscord));
    }

    bool Ship::validation_setting_ship_of_near_cords(std::vector<Cords>& cordsOfShipAndNearshipscord) {
        for (auto near_cord : cordsOfShipAndNearshipscord) {
            for (Cords cor : cordsOfShip) {
                if (near_cord.x == cor.x && near_cord.y == cor.y)
                    return false;
            }
        }
        return true;
    }

    bool Ship::check_cordsOfShipAndNearshipscord(int x, int y, std::vector<Cords>& cordsOfShipAndNearshipscord) {
        auto it = std::find_if(cordsOfShipAndNearshipscord.begin(), cordsOfShipAndNearshipscord.end(), [=](const Cords& c) {
            return c.x == x && c.y == y;
            });
        if (it == cordsOfShipAndNearshipscord.end())
            return true;

        return false;
    }

    bool Ship::validationOfCordInVectorOfNearCordsOfShips(std::vector<Cords>& cordsOfShipAndNearshipscord) {
        if (rotate == Rotate::Horizontal) {
            for (int i = x; i < x + lenght; ++i) {
                if (!check_cordsOfShipAndNearshipscord(i, y, cordsOfShipAndNearshipscord)){
                    return true;
                }
            }
        }
        else {
            for (int j = y; j < y + lenght; ++j) {
                if (!check_cordsOfShipAndNearshipscord(x, j, cordsOfShipAndNearshipscord)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Ship::bordersCondition() {

        if (rotate == Rotate::Horizontal) {
            if (x + lenght > 9 || x < 0 || y > 9 || y < 0){
                return true;
            }
        }
        else {
            if (x > 9 || x < 1 || y + lenght > 9 || y < 0){
                return true;
            }
        }     
        return false;
    }

    bool Ship::check_rotate(std::vector<Cords>& cordsOfShipAndNearshipscord) {

        Cords head = *(cordsOfShip.begin());

        if (rotate == Rotate::Vertical) {
            for (int col = head.x; col < head.x + lenght; ++col) {
                if (!check_cordsOfShipAndNearshipscord(col, head.y, cordsOfShipAndNearshipscord))
                    return false;
                if (col < 0 || col > size_of_board - 1 || head.y < 0 || head.y > size_of_board - 1)
                    return false;
            }
        }
        else {
            for (int row = head.y; row < head.y + lenght; ++row) {
                if (!check_cordsOfShipAndNearshipscord(head.x, row, cordsOfShipAndNearshipscord))
                    return false;
                if (head.x < 0 || head.x > size_of_board - 1 || row < 0 || row > size_of_board - 1)
                    return false;
            }
        }
        return true;
    }

    void Ship::rotate_ship() {

        Cords head = *(cordsOfShip.begin());

        if (rotate == Rotate::Vertical) {
            cordsOfShip.clear();
            for (int col = head.x; col < head.x + lenght; ++col) {
                cordsOfShip.push_back(Cords(col, head.y));
            }
            rotate = Rotate::Horizontal;
        }
        else {
            cordsOfShip.clear();
            for (int row = head.y; row < head.y + lenght; ++row) {
                cordsOfShip.push_back(Cords(head.x, row));
            }
            rotate = Rotate::Vertical;
        }
    }

    void Ship::change_cords_to_move(int dx, int dy) {
        
        std::for_each(cordsOfShip.begin(), cordsOfShip.end(), [=](Cords& p){
            p.x = p.x + dx; p.y = p.y + dy;
            });
    }

    bool Ship::check_dif(std::vector<Cords>& cordsOfShips, int dx, int dy) {
   
            for (Cords cor : cordsOfShip) {
                if (cor.x + dx < 0 || cor.x + dx > size_of_board - 1 || cor.y + dy < 0 || cor.y + dy > size_of_board - 1)
                    return false;
                if(!check_cordsOfShipAndNearshipscord(cor.x + dx, cor.y + dy, cordsOfShips))
                    return false;
            } 
        return true;
    }


    // УСТАНОВКА КОРАБЛЕЙ ПРОТИВНИКА (компьютера)

    void Ship::AddCordsOffComputerShip(std::vector<Cords>& cordsOfShipAndNearshipscordOfComputer, std::vector <std::vector<int>>& fieldOfDisplay) {
        this->add_temporary_points_of_ship();
        this->addNearCords(cordsOfShipAndNearshipscordOfComputer); // добавляем координаты окружающие корабль
    }

