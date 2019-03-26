/*
 * File: Hero.h
 * ------------
 * This file exports class <code>Hero</code>. Hero could move, collide and
 * trigger different activities.
 */

#ifndef Hero_H
#define Hero_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Hero: public QObject, public QGraphicsPixmapItem
{   Q_OBJECT
public:
    // constructor
    Hero(QGraphicsItem* parent=nullptr);

    // public methods
    void keyPressEvent(QKeyEvent * event);
    void show();
    void safeClearFloor();
    void updateItemInfo(int aroundID);
    void checkEnd(int aroundID);

    bool checkWalkable(int aroundID);
    bool checkPickable(int aroundID);
    bool checkNPC(int aroundID);
    bool checkMonster(int aroundID);
    bool checkDoor(int aroundID);
    bool checkUpstaris(int aroundID);
    bool checkDownstairs(int aroundID);
    bool checkOpen(int aroundID);
    bool checkWin(int aroundID);

    int getPosX();
    int getPosY();
    int getHp();
    int getAtk();
    int getDef();
    int getLv();
    int getMoney();
    int getExperience();
    int getFloor();
    int getRedKey();
    int getBlueKey();
    int getYellowKey();
    bool getFlyFloor();
    bool getMonsterInfo();
    void setHp(int newHp);
    void setAtk(int newAtk);
    void setDef(int newDef);
    void setLv(int newLv);
    void setMoney(int newMoney);
    void setExperience(int newExperience);
    void setFloor(int newFloor);
    void setRedKey(int newkey);
    void setBlueKey(int newkey);
    void setYellowKey(int newkey);
    bool checkFloorVisited(int floor);
public slots:
    void upChangePicture();
    void downChangePicture();
    void leftChangePicture();
    void rightChangePicture();
    void setFocusToSelf();

private:
    // private variables
    int hp,lv,atk,def,money,experience;
    bool flyFloor, monsterInfo;
    int redkey,bluekey,yellowkey;
    int floor;
    int aroundInfo[4];
    bool floorVisited[4];

    QImage hero_up1_img, hero_up2_img;
    QImage hero_down1_img, hero_down2_img;
    QImage hero_left1_img, hero_left2_img;
    QImage hero_right1_img, hero_right2_img;

    // private methods
    void getAroundId();
    bool floorVisitedBefore(int floorID);
    void floorVisitedNew(int floorID);
};

#endif // Hero_H
