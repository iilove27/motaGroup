#ifndef MAP_H
#define MAP_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "unwalkable.h"
#include "hero.h"
#include "monster.h"

class map
{
public:
    map();
    Hero * hero;
    Monster * mons;
    void getMap2D(int floor);
    int getHeroPosX();
    int getHeroPosY();
    void show();
};

#endif // MAP_H
