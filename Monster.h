#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class Monster: public QGraphicsPixmapItem
{
public:
    Monster(QGraphicsItem * parent=0);
    void init(int);
    void show(int);

private:
    char name[30];
    int id,hp,atk,def,money,experience,special;
    int state, positionx, positiony;

};

#endif // MONSTER_H
