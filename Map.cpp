/*
 * File: Map.cpp
 * --------------------
 * This file implements Map.h interface.
 */

#include <QTextStream>
#include <iostream>
#include <fstream>
#include <QDebug>
#include "Map.h"
#include "Game.h"
#include "Hero.h"
using namespace std;

extern Game* game;

Map::Map(string filename)
{

    // TO DO: use QFile/QTextStream or other ways to read from relative path
    ifstream file(filename);
    if (!file.is_open()) {
        qDebug() << "Could not open map data file (map.dat).";
    }
    else {
        for (int map_f = 0; map_f < 4; map_f++) {
            for (int map_i = 0; map_i < 11; map_i++) {
                for (int map_j = 0; map_j < 11; map_j++) {
                    file >> map2D[map_f][map_i][map_j];
                    int map_id = map2D[map_f][map_i][map_j];
                    if (map_id > 100 && map_id < 200)
                    {
                        npcs[map_id % 100] = new NPC(map_id);   // create NPC
                    }
                }
            }
        }
    }
}

/*
 * Implementation notes: show(int floor)
 * -----------------------------------
 * Draw the map based on the floor <code>f</code>.
 */

void Map::show(int f)
{
    // initialize
    for (int j = 0; j < 11; j++)
        for (int i = 0; i < 11; i++) {
            mons[j*11+i] = nullptr;
            items[j*11+i] = nullptr;
            wall[j*11+i] = nullptr;
        }

    // create unwalkable, npcs, monsters, items
    for (int j = 0; j < 11; j++)
        for (int i = 0; i < 11; i++)
        {
            int mapId = map2D[f][j][i];
            int mapIndex = j*11+i;
            switch (mapId)
            {
            case 1:
                wall[mapIndex] = new unwalkable(1);
                wall[mapIndex]->setPos(i*40 + 100, j*40);
                wall[mapIndex]->show();
                break;
            case 2:
                wall[mapIndex] = new unwalkable(2);
                wall[mapIndex]->setPos(i*40 + 100, j*40);
                wall[mapIndex]->show();
                break;
            case 3:
                wall[mapIndex] = new unwalkable(3);
                wall[mapIndex]->setPos(i*40 + 100, j*40);
                wall[mapIndex]->show();
                break;
            case 4: case 5: case 6: case 7: case 301: case 303: case 304: addItemToScene(i, j, mapId, items); break;
            case 101: case 102:case 103: addNPCToScene(i, j, mapId); break;
            case 201: case 202: case 203: addMonsterToScene(i, j, mapId, mons); break;
            }
        }

    // put everything on the scene
    for (int j = 0; j < 11; j++)
        for (int i = 0; i < 11; i++)
        {
            int mapId = map2D[f][j][i];
            int mapIndex = j*11+i;
            switch (mapId)
            {
            case 1: case 2: case 3: game->scene->addItem(wall[mapIndex]); break;
            case 4: case 5: case 6: case 7: case 301: case 303: case 304: game->scene->addItem(items[mapIndex]); break;
            case 101: case 102:case 103: game->scene->addItem(npcs[mapId % 100]); break;
            case 201: case 202: case 203: game->scene->addItem(mons[mapIndex]); break;
            }
        }
}

/*
 * Implementation notes: addXToScene()
 * -----------------------------------
 * Add Monsters, NPCs, Items to scene.
 */

void Map::addMonsterToScene(int i, int j, int monsID, Monster *mons[]) {
    int monsIndex = j*11+i;
    mons[monsIndex] = new Monster(monsID);
    mons[monsIndex]->setPos(i * 40 + 100, j * 40);
    mons[monsIndex]->show();
}

void Map::addNPCToScene(int i, int j, int npcID)
{
    int npcIndex = npcID % 100;
    npcs[npcIndex]->setPos(i * 40 + 100, j * 40);
    npcs[npcIndex]->show();
}

void Map::addItemToScene(int i, int j, int itemID, Item* items[])
{
    int itemIndex = j*11+i;
    items[itemIndex] = new Item(itemID);
    items[itemIndex]->setPos(i * 40 + 100, j * 40);
    items[itemIndex]->show();
}

/*
 * Implementation notes: updateMap()
 * ---------------------------------
 * Update <code>map2D</code> after picking item, battling, opening door.
 */

void Map::updateMap(int f, int i, int j, int newValue)
{
    map2D[f][j][i] = newValue;
}

void Map::findPosition(int* x, int* y, int ID, int f)
{
    for (int j = 0; j < 11; j++)
        for (int i = 0; i < 11; i++)
        {
            if (map2D[f][j][i] == ID)  {
                *x = i;
                *y = j;
                return;
            }
        }
}

/*
 * Implementation notes: saveMapintoRecord(string filename)
 * --------------------------------------------------------
 * Save current map into file.
 */

void Map::saveMapintoRecord(string filename)
{
    fstream  storeFile;
    storeFile.open(filename, ios::out|ios::trunc);

    for (int map_f = 0; map_f < 4; map_f++) {
        for (int map_i = 0; map_i < 11; map_i++) {
            for (int map_j = 0; map_j < 11; map_j++) {
                storeFile << map2D[map_f][map_i][map_j]<<' ';
            }
            storeFile<<endl;
        }
       storeFile<<endl;
    }
    storeFile.close();
}
