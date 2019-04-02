/*
 * File: Monster.cpp
 * --------------------
 * This file implements Monster.h interface.
 */

#include "Monster.h"
#include <QGraphicsRectItem>

Monster::Monster(int monsterID, QGraphicsItem *parent): QGraphicsPixmapItem (parent)
{
    id = monsterID;     // set id

    // set parameters
    switch(id)
    {
    case 201: name="didi"; hp=50; atk=20; def=1; money=100; experience=100; break;
    case 202: name="gege"; hp=20; atk=11; def=1; money=10; experience=10; break;
    case 203: name="gongzhu"; hp=2000; atk=20; def=1; money=1; experience=1; break;
    }
}

/*
 * Implementation notes: show()
 * ----------------------------
 * Draw the monster.
 */

void Monster::show()
{
    QString monster_img_path;
    QImage monster_img;

    // find image path
    switch (id){
        case 201: monster_img_path = ":/images/201.png"; break;
        case 202: monster_img_path = ":/images/202.png"; break;
        case 203: monster_img_path = ":/images/203.png"; break;
    }

    // load and draw image
    monster_img.load(monster_img_path);
    QPixmap monster_pic=QPixmap::fromImage(monster_img.scaled(40, 40));
    setPixmap(monster_pic);
}

/*
 * Implementation notes: getX()
 * --------------------------
 * Return private attributes of monsters.
 */

int Monster::getId()
{
    return id;
}

int Monster::getHp()
{
    return hp;
}

int Monster::getAtk()
{
    return atk;
}

int Monster::getDef()
{
    return def;
}

int Monster::getMoney()
{
    return money;
}

int Monster::getExperience()
{
    return experience;
}

QString Monster::getName()
{
    return name;
}
