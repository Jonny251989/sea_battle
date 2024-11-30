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
            for (int y = std::max(cord.y_ - 1, 0); y <= std::min(cord.y_ + 1, size_of_board - 1); ++y) {
                for (int x = std::max(cord.x_ - 1, 0); x <= std::min(cord.x_ + 1, size_of_board - 1); ++x) {
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
                if (near_cord.x_ == cor.x_ && near_cord.y_ == cor.y_)
                    return false;
            }
        }
        return true;
    }

    bool Ship::check_cordsOfShipAndNearshipscord(int x, int y, std::vector<Cords>& cordsOfShipAndNearshipscord) {
        auto it = std::find_if(cordsOfShipAndNearshipscord.begin(), cordsOfShipAndNearshipscord.end(), [=](const Cords& c) {
            return c.x_ == x && c.y_ == y;
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
            for (int col = head.x_; col < head.x_ + lenght; ++col) {
                if (!check_cordsOfShipAndNearshipscord(col, head.y_, cordsOfShipAndNearshipscord))
                    return false;
                if (col < 0 || col > size_of_board - 1 || head.y_ < 0 || head.y_ > size_of_board - 1)
                    return false;
            }
        }
        else {
            for (int row = head.y_; row < head.y_ + lenght; ++row) {
                if (!check_cordsOfShipAndNearshipscord(head.x_, row, cordsOfShipAndNearshipscord))
                    return false;
                if (head.x_ < 0 || head.x_ > size_of_board - 1 || row < 0 || row > size_of_board - 1)
                    return false;
            }
        }
        return true;
    }

    void Ship::rotate_ship() {

        Cords head = *(cordsOfShip.begin());

        if (rotate == Rotate::Vertical) {
            cordsOfShip.clear();
            for (int col = head.x_; col < head.x_ + lenght; ++col) {
                cordsOfShip.push_back(Cords(col, head.y_));
            }
            rotate = Rotate::Horizontal;
        }
        else {
            cordsOfShip.clear();
            for (int row = head.y_; row < head.y_ + lenght; ++row) {
                cordsOfShip.push_back(Cords(head.x_, row));
            }
            rotate = Rotate::Vertical;
        }
    }

    void Ship::change_cords_to_move(int dx, int dy) {
        
        std::for_each(cordsOfShip.begin(), cordsOfShip.end(), [=](Cords& p){
            p.x_ = p.x_ + dx; p.y_ = p.y_ + dy;
            });
    }

    bool Ship::check_dif(std::vector<Cords>& cordsOfShips, int dx, int dy) {
   
            for (Cords cor : cordsOfShip) {
                if (cor.x_ + dx < 0 || cor.x_ + dx > size_of_board - 1 || cor.y_ + dy < 0 || cor.y_ + dy > size_of_board - 1)
                    return false;
                if(!check_cordsOfShipAndNearshipscord(cor.x_ + dx, cor.y_ + dy, cordsOfShips))
                    return false;
            } 
        return true;
    }


    // УСТАНОВКА КОРАБЛЕЙ ПРОТИВНИКА (компьютера)

    void Ship::AddCordsOffComputerShip(std::vector<Cords>& cordsOfShipAndNearshipscordOfComputer, std::vector <std::vector<int>>& fieldOfDisplay) {
        this->add_temporary_points_of_ship();
        this->addNearCords(cordsOfShipAndNearshipscordOfComputer); // добавляем координаты окружающие корабль
    }

