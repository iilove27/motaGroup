/*
 * File: battle.h
 * --------------
 * This file exports a class <code>battle</code>. Information about monster
 * and hero would be input. After checking whether the hero is stronger than
 * monster, <code>battleFrame</code> shows with Hps of hero and monster
 * decreasing in turn. Delete frame and set focus back to <code>Hero</code>.
 */

#ifndef BATTLE_H
#define BATTLE_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QObject>
#include <QTimer>
#include "Hero.h"
#include "Monster.h"
#include "Game.h"

class battle: public QObject
{   Q_OBJECT
public:
    // constructor
    battle(Monster* monster, Hero* hero);

    // public methods
    void battleFrameShow(Monster* monster, Hero* hero);
    bool checkBattle();
    void updateText();
public slots:
    void battleOnce();  // show

private:
    // private variables
    int monsterId, monsterHp, monsterAtk, monsterDef;
    int heroHp, heroAtk, heroDef;
    int monsterHarm, heroHarm;  // harm = atk - def

    QString monsterHpInfo, monsterAtkInfo, monsterDefInfo;
    QString heroHpInfo, heroAtkInfo, heroDefInfo;

    QGraphicsTextItem* monsterHpText,* monsterAtkText,* monsterDefText;
    QGraphicsTextItem* heroHpText,* heroAtkText,* heroDefText;
    QGraphicsRectItem* battleFrame;
    QGraphicsPixmapItem* hero_img_battle;
    QGraphicsPixmapItem* monster_img_battle;

    QTimer* timer;
};

#endif // BATTLE_H
