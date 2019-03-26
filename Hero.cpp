#include <hero.h>
#include <QKeyEvent>
#include <bullet.h>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <monster.h>
#include <game.h>
#include <stdlib.h>
#include <Msgboard.h>
#include <unistd.h>
extern Game * game;

Hero::Hero(QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
}

void Hero::init()
{
    lv = 1;
    hp = 1000;
    atk = 10;
    def = 10;
    money = 0;
    experience = 0;
    redkey = 0;
    bluekey = 0;
    yellowkey = 0;
    special = 0;
    floor = 0;
}

void Hero::keyPressEvent(QKeyEvent *event)
{
    size_t unwalkableArraySize = sizeof(unwalkableArray) / sizeof(int);
    int *end = unwalkableArray + unwalkableArraySize;
//    qDebug() << posX << posY << map2D[posY][posX-1];



    // 这一段我正在尝试换focus，但是会崩溃，我也会崩溃 ：）。
    // 最初的方法是碰到怪就算是碰撞，然后就把怪去了，之后改成如果移动的方向是怪，就开始战斗

    if (event->key() == Qt::Key_Left) {
        int *findResult = std::find(unwalkableArray, end, aroundInfo[2]);
        if (aroundInfo[2] == 0){
            if (pos().x() > 0) {
                setPos(x()-40, y());
//                if (checkEnd())
//                {
//                    gameOver();
//                }


//                if (checkEncounter()) {
//                    QList<QGraphicsItem *> colliding = collidingItems();
//                    for (int i = 0, n = colliding.size(); i < n; ++i) {
//                        if (typeid(*(colliding[i])) == typeid(Monster)) {
//                            scene()->removeItem(colliding[i]);
//                            delete colliding[i];
//                        }
//                    }
//                }
            }
        }
        else {  // encounter npc, monster, items, can be encapsulated in functions later
            int id = aroundInfo[2];
            if (id == 44) {
                MsgBoard * msg = new MsgBoard(QString("Welcome."), pos().x(), pos().y(), 200, 150);
                game->scene->addItem(msg);
                msg->setFlag(QGraphicsItem::ItemIsFocusable);
                msg->setFocus();
//                game->drawPanel(pos().x(), pos().y(), 200, 150, Qt::gray, 0.85);
//                QGraphicsTextItem * text = new QGraphicsTextItem(QString("Welcome to Magic Tower!"));
//                text->setPos(pos().x()+20, pos().y()+20);
//                game->scene->addItem(text);
            }
        }
    }

    else if (event->key() == Qt::Key_Right) {
        if (aroundInfo[3]==0){
            if (pos().x()+40 < 440) {
                setPos(x()+40, y());
                if (checkEncounter()) {
                    QList<QGraphicsItem *> colliding = collidingItems();
                    for (int i = 0, n = colliding.size(); i < n; ++i) {
                        if (typeid(*(colliding[i])) == typeid(Monster)) {
                            scene()->removeItem(colliding[i]);
                            delete colliding[i];
                        }
                    }
                }
            }
        }
    }
    else if (event->key() == Qt::Key_Up) {
        if (aroundInfo[0] == 0){
            if(pos().y() > 0){
                setPos(x(), y()-40);
                if (checkEncounter()) {
                    QList<QGraphicsItem *> colliding = collidingItems();
                    for (int i = 0, n = colliding.size(); i < n; ++i) {
                        if (typeid(*(colliding[i])) == typeid(Monster)) {
                            scene()->removeItem(colliding[i]);
                            delete colliding[i];
                        }
                    }
                }
            }
        }
    }
    else if (event->key() == Qt::Key_Down) {
        if (aroundInfo[1] == 0){
            if (pos().y()+40 < 440) {
                setPos(x(), y()+40);
                if (checkEncounter()) {
                    QList<QGraphicsItem *> colliding = collidingItems();
                    for (int i = 0, n = colliding.size(); i < n; ++i) {
                        if (typeid(*(colliding[i])) == typeid(Monster)) {
                            scene()->removeItem(colliding[i]);
                            delete colliding[i];
                        }
                    }
                }
            }
        }
    }
    if (aroundInfo[0]==91) game->gameOver();
    getAroundId();  // 移动一步后要看看周围是什么
}


bool Hero::checkEncounter()
{
    QList<QGraphicsItem *> colliding = collidingItems();
    for (int i = 0, n = colliding.size(); i < n; ++i) {
        if (typeid(*(colliding[i])) == typeid(Monster)) {
            return true;
        }
    }
    return false;
}

void Hero::show()
{
    QString hero_img_path;
    QImage hero_img;
    hero_img_path = ":/images/hero_front.png";
    hero_img.load(hero_img_path);
    QPixmap hero_pic=QPixmap::fromImage(hero_img.scaled(40, 40));
    setPixmap(hero_pic);
}

int Hero::getPosX()
{
    return int((pos().x()-100) / 40);
}

int Hero::getPosY()
{
    return int(pos().y() / 40);
}

bool Hero::checkEnd()
{
    if (floor==0 && map2D[getPosY()-1][getPosX()]==91) return true;
    else return false;
}

void Hero::setFocusToSelf()
{
    this->setFocus();
}

void Hero::getAroundId()
{
    int posX = getPosX();
    int posY = getPosY();   //TODO: 尚未implement边界不能走的情况（边界的aroundInfo会异常，之后再改，体力活
    qDebug() << posX << posY;
    aroundInfo[0] = map2D[posY-1][posX];
    aroundInfo[1] = map2D[posY+1][posX];
    aroundInfo[2] = map2D[posY][posX-1];
    aroundInfo[3] = map2D[posY][posX+1];
}




