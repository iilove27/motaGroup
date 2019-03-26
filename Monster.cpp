#include "monster.h"
#include <QGraphicsRectItem>
#include <QDebug>

Monster::Monster(QGraphicsItem *parent): QGraphicsPixmapItem (parent) {

}


void Monster::init(int t=0)
{
    id = t;
    switch(t)
    {
        case 0: positionx = 0; positiony=0;hp=50;atk=20;def=1;money=1;experience=1;special=0; break;
    }
}

void Monster::show(int monsID)
{
    QString monster_img_path;
    QImage monster_img;
    if (monsID == 0){
    monster_img_path = ":/images/monster.png";}
    monster_img.load(monster_img_path);
    QPixmap monster_pic=QPixmap::fromImage(monster_img.scaled(40, 40));
    setPixmap(monster_pic);
}
