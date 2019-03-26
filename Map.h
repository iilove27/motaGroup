/*
 * File: Map.h
 * ------------
 * This file exports the class <code>Map</code>.
 */

#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "Unwalkable.h"
#include "Hero.h"
#include "Monster.h"
#include "npc.h"
#include "Item.h"
using namespace std;

class Map
{
public:
    // constructor
    Map(string filename);

    // public variables
    int map2D[4][11][11];   // store map information matrix
    NPC * npcs[100];        // store all npc information
    Monster * mons[121];    // store monster informatin of specific floor
    Item * items[121];      // store item informatin of specific floor
    unwalkable * wall[121]; // store wall informatin of specific floor

    // public methods
    void show(int floor);
    void addMonsterToScene(int i, int j, int monsterID, Monster* monsters[]);
    void addNPCToScene(int i, int j, int npcID);
    void addItemToScene(int i, int j, int itemID, Item* items[]);
    void updateMap(int f, int i, int j, int newValue);  // update map information matrix
    void findPosition(int* x, int* y, int ID, int f);
    void saveMapintoRecord(string filename);
};

#endif // MAP_H
