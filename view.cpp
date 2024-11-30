#include "view.h"
#include <QColor>


My_view::My_view(QWidget *parent, Gamer* gamer, Computer* computer) : QGraphicsView(parent), gamer_(gamer), computer_(computer){
    setFocusPolicy(Qt::NoFocus);
    this->setFixedHeight(1150);
    this->setFixedWidth(1150);
    this->setGeometry(0,0, 1150, 1150);
    this->setMinimumSize(1150, 1150);

    scene = new QGraphicsScene(this);
    this->setScene(scene);
    scene->setSceneRect(0,0, 1150, 1150); // Устанавливаем область графической сцены
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    this->draw_field();
}

void My_view::reload_all_objects_computer() {

    for (auto item : m_moved_items_computer) {
        scene->removeItem(item);
        delete item;
    }
    m_moved_items_computer.clear();

    std::vector<Ship*> ships_items_computer = computer_->getshipsOfComputer();
    for(auto ship: ships_items_computer){
        std::vector<Cords> corsdOfShipComputer = ship->getCordsOfShip();

        for (auto it = corsdOfShipComputer.begin(); it != corsdOfShipComputer.end(); ++it) {
            QGraphicsRectItem* ship_item_computer = new QGraphicsRectItem((it->x + 11) * w_rect,
                                                                it->y * h_rect,
                                                                w_rect, h_rect);
        
            ship_item_computer->setBrush(QBrush(QColor(159,97,4,255)));
            scene->addItem(ship_item_computer);
            m_moved_items_computer.push_back(ship_item_computer);
        }
    }
}

void My_view::game_over(){
        QMessageBox::information(
    this,
    tr("Fail!"),
    tr("Game Over!"));
}

void My_view::reload_all_fields_item_of_computer(){
        QPen pen_free_item(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    for (auto item : m_moved_fields_item_of_computer) {
        scene->removeItem(item);
        delete item;
    }
    m_moved_fields_item_of_computer.clear();

    std::vector<std::vector<MapItem>> field_item_computer = computer_->getFieldOfComputersItem();

    // SHIP, EMPTY, MISS, WRECKED, DESTROYED, SURROUNDING, REFERENCE_POINTS
    for(int rows = 0; rows < SIZE_FIELD ; ++rows){
        for(int columns = 0; columns < SIZE_FIELD; ++columns){
            auto item = new QGraphicsRectItem(
                columns * (w_rect - 10), (rows + SIZE_FIELD + 3)* (h_rect - 10),
                w_rect - 10, h_rect - 10);

            QGraphicsTextItem* cost;

            switch(field_item_computer[rows][columns]){

                case MapItem::DESTROYED:{
                    cost = new QGraphicsTextItem("DSTR");
                    item->setBrush(QBrush(QColor(179,10,10,255)));
                    break;
                }
                case MapItem::SHIP:{
                    cost = new QGraphicsTextItem("SH");
                    item->setBrush(QBrush(QColor(230,204,36,255)));
                    break;
                }
                case MapItem::EMPTY:{
                    cost = new QGraphicsTextItem("EMP");
                    item->setBrush(QBrush(QColor(224,224,254,255)));
                    break;
                }
                case MapItem::MISS:{
                    cost = new QGraphicsTextItem("MS");
                    item->setBrush(QBrush(QColor(245,90,90,255)));
                    break;
                }
                case MapItem::WRECKED:{
                    cost = new QGraphicsTextItem("WRK");
                    item->setBrush(QBrush(QColor(255, 0, 0, 255)));
                    break;
                }
                case MapItem::SURROUNDING:{
                    cost = new QGraphicsTextItem("SRD");
                    item->setBrush(QBrush(QColor(0, 204, 255,255)));
                    break;
                }
                case MapItem::REFERENCE_POINTS:{
                   cost = new QGraphicsTextItem("RP");
                   item->setBrush(QBrush(QColor(0, 255, 34, 255)));
                    break;
                }
            }
            cost->setPos((columns) * (w_rect - 10), (rows + 13) * (h_rect - 10));
            scene->addItem(item);
            scene->addItem(cost);
            m_moved_fields_item_of_computer.push_back(cost);
        }
    }
}

void My_view::reload_all_weights_of_computer(){

    QPen pen_free_item(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    for (auto item : m_moved_weights_of_computer) {
        scene->removeItem(item);
        delete item;
    }
    m_moved_weights_of_computer.clear();

    std::vector<std::vector<int>> field_costs_computer = computer_->getVectorOfCosts();
    for(int rows = 0; rows < SIZE_FIELD ; ++rows){
        for(int columns = 0; columns < SIZE_FIELD; ++columns){

            QGraphicsTextItem* cost = new QGraphicsTextItem(QString::number(field_costs_computer[rows][columns]));
            
             auto item = new QGraphicsRectItem(
                (columns + SIZE_FIELD + 3)* (w_rect - 10), (rows + SIZE_FIELD + 3)* (h_rect - 10),
                w_rect - 10, h_rect - 10);

            switch(field_costs_computer[rows][columns]){

                case 0:{
                    item->setBrush(QBrush(QColor(228, 242, 242, 255)));
                    break;
                }
                case 1:{
                    item->setBrush(QBrush(QColor(201, 247, 247, 255)));
                    break;
                }
                case 2:{
                    item->setBrush(QBrush(QColor(80, 219, 240,255)));
                    break;
                }
                case 3:{
                    item->setBrush(QBrush(QColor(0, 204, 0,255)));
                    break;
                }
                case 4:{
                    item->setBrush(QBrush(QColor(255, 0, 0, 255)));
                    break;
                }
            }    
            cost->setPos((columns + 13) * (w_rect - 10), (rows + 13) * (h_rect - 10));
            scene->addItem(item);
            scene->addItem(cost);
            m_moved_weights_of_computer.push_back(cost);
        }
    }
}

void My_view::draw_games_steps(){
    for (auto item : m_moved_games_item) {
        scene->removeItem(item);
        delete item;
    }
    m_moved_games_item.clear();

    auto items_gamer = gamer_->getFieldMapOfGamer();
    auto items_computer = computer_->getFieldOfComputersItem();

    for (size_t y = 0; y < SIZE_FIELD; ++y ) {
        for (size_t x = 0; x < SIZE_FIELD; ++x ) {
            QGraphicsRectItem* item_gamer = new QGraphicsRectItem((x + 11) * w_rect,
                                                                    y * h_rect,
                                                                    w_rect, h_rect);
            QGraphicsRectItem* item_computer = new QGraphicsRectItem(x * w_rect,
                                                                    y * h_rect,
                                                                    w_rect, h_rect);                                                                    
            switch(items_gamer[y][x]){
                case MapItem::SHIP:
                    item_gamer->setBrush(QBrush(QColor(Qt::darkGray)));
                    break;
                case MapItem::WRECKED:
                    item_gamer->setBrush(QBrush(QColor(Qt::red)));
                    break;
                case MapItem::DESTROYED:
                    item_gamer->setBrush(QBrush(QColor(Qt::darkRed)));
                    break;
                case MapItem::MISS:
                    item_gamer->setBrush(QBrush(QColor(Qt::darkYellow)));
                    break;
                case MapItem::SURROUNDING:
                    item_gamer->setBrush(QBrush(QColor(Qt::darkGreen)));
                    break;          
            }

            switch(items_computer[y][x]){
                case MapItem::SHIP:
                    item_computer->setBrush(QBrush(QColor(Qt::darkGray)));
                    break;
                case MapItem::WRECKED:
                    item_computer->setBrush(QBrush(QColor(Qt::red)));
                    break;
                case MapItem::DESTROYED:
                    item_computer->setBrush(QBrush(QColor(Qt::darkRed)));
                    break;
                case MapItem::MISS:
                    item_computer->setBrush(QBrush(QColor(Qt::darkYellow)));
                    break;
                case MapItem::SURROUNDING:
                    item_computer->setBrush(QBrush(QColor(Qt::darkGreen)));
                    break;          
            }

            scene->addItem(item_gamer);
            m_moved_games_item.push_back(item_gamer);

            scene->addItem(item_computer);
            m_moved_games_item.push_back(item_computer);

        }
    }
}

void My_view::reload_all_objects_gamer(Ship* ship) {

    for (auto item : m_moved_items) {
        scene->removeItem(item);
        delete item;
    }
    m_moved_items.clear();

    auto ship_items = ship->getCordsOfShip();
   
    for (auto it = ship_items.begin(); it != ship_items.end(); ++it) {
        QGraphicsRectItem* ship_item = new QGraphicsRectItem(it->x * w_rect,
                                                                it->y * h_rect,
                                                                w_rect, h_rect);
        
        ship_item->setBrush(QBrush(QColor(Qt::darkGray)));
        scene->addItem(ship_item);
        m_moved_items.push_back(ship_item);
    }


    std::vector<Ship*> ships_items = gamer_->getshipsOfGamer();
    for(auto ship: ships_items){
        std::vector<Cords> corsdOfShip = ship->getCordsOfShip();
        for (auto it = corsdOfShip.begin(); it != corsdOfShip.end(); ++it) {
            QGraphicsRectItem* ship_item = new QGraphicsRectItem(it->x * w_rect,
                                                                    it->y * h_rect,
                                                                    w_rect, h_rect);
            
            ship_item->setBrush(QBrush(QColor(Qt::darkGray)));
            scene->addItem(ship_item);
            m_moved_items.push_back(ship_item);
            }
    }
}

void My_view::draw_cords_for_attack(int x, int y){

for (auto item : m_moved_points_attack) {
        scene->removeItem(item);
        delete item;
    }
    m_moved_points_attack.clear();

    auto item = new QGraphicsRectItem;

    item->setRect((x + 11) * w_rect, y * h_rect, w_rect, h_rect);
    item->setBrush(QBrush(QColor(Qt::gray)));
    scene->addItem(item);
    m_moved_points_attack.push_back(item);
}

void My_view::draw_field(){
    QPen pen_free_item(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    for(int rows = 0; rows < SIZE_FIELD; ++rows){
        for(int columns = 0; columns < SIZE_FIELD; ++columns){
            auto item = new QGraphicsRectItem(
                columns * w_rect, rows * h_rect,
                w_rect, h_rect);
            item->setPen(pen_free_item);
            item->setZValue(0);
            scene->addItem(item);
        }
    }

    for(int rows = 0; rows < SIZE_FIELD; ++rows){
        for(int columns = SIZE_FIELD + 1; columns < 2*SIZE_FIELD + 1; ++columns){
            auto item = new QGraphicsRectItem(
                columns * w_rect, rows * h_rect,
                w_rect, h_rect);
            item->setPen(pen_free_item);
            item->setZValue(0);
            scene->addItem(item);
        }
    }
}

My_view::~My_view(){
    
}

