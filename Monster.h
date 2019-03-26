/*
 * File: Monster.h
 * ------------
 * This file exports the class <code>Monster</code>, which is used to store
 * relevant information about specific monster.
 */

#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class Monster: public QGraphicsPixmapItem
{
public:
    // constructor
    Monster(int monsterID, QGraphicsItem* parent=0);

    // public methods
    void show();
    void battle();
    int getId();
    int getHp();
    int getAtk();
    int getDef();
    int getMoney();
    int getExperience();
    QString getName();

private:
    // private variables
    int id, hp, atk, def, money, experience;
    QString name;
};

#endif // MONSTER_H
