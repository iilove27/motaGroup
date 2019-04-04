/*
 * File: Hero.cpp
 * --------------------
 * This file implements Hero.h interface.
 */

#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <Msgboard.h>
#include <unistd.h>
#include <QTimer>
#include "Unwalkable.h"
#include "Map.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "battle.h"
#include "communication.h"
#include "business.h"
#include "saveload.h"
#include "backpack.h"
#include "npcflygame.h"
using namespace std;

extern Game * game;

Hero::Hero(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // default
    lv = 1;
    hp = 1000;
    atk = 10;
    def = 10;
    money = 0;
    experience = 0;
    redkey = 1;
    bluekey = 0;
    yellowkey = 0;
    floor = 0;
    flyFloor = false;
    monsterInfo = false;
    floorVisited[0] = true;
    for (int floor_i = 1; floor_i < 4; floor_i++) floorVisited[floor_i] = false;

    // load all image
    hero_up1_img.load(":/images/up1.png");
    hero_up2_img.load(":/images/up2.png");
    hero_down1_img.load(":/images/down1.png");
    hero_down2_img.load(":/images/down2.png");
    hero_left1_img.load(":/images/left1.png");
    hero_left2_img.load(":/images/left2.png");
    hero_right1_img.load(":/images/right1.png");
    hero_right2_img.load(":/images/right2.png");
}

void Hero::keyPressEvent(QKeyEvent *event)
{
     getAroundId();  // get id around after one step
    // Key_S
    if (event->key() == Qt::Key_S) {
        game->showSave();
    }

    // Key_L
    if (event->key() == Qt::Key_L) {
        game->showLoad();
    }

    // Key_B
    if (event->key() == Qt::Key_B) {
        game->backpackSys->showFrame();
    }

    // Key_Left
    if (event->key() == Qt::Key_Left) {
        int aroundId = aroundInfo[2];   // get colliding item

        if (checkWalkable(aroundId)){
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(leftChangePicture()));

            setPos(x()-40, y());    // walk if hero could walk
        }
        else if (checkPickable(aroundId)) {
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(leftChangePicture()));

            setPos(x()-40, y());    // walk

            // update map & delete item
            game->maps->updateMap(floor, getPosX(), getPosY(), 0);
            safeClearFloor();
            game->renderFloor(floor);

            // update item info
            updateItemInfo(aroundId);
            game->updateInfo();

            // show update message
            QString updateText;
            switch (aroundId) {
            case 301: updateText = "You get 3 ATKs !"; break;
            case 303: updateText = "You get Fly Floor Tools !"; game->backpackSys->addNewItem(303); break;
            case 304: updateText = "You get Monster Research Tools !"; game->backpackSys->addNewItem(304); break;
            }
            MsgBoard * msg = new MsgBoard(updateText, 100, 100, 440, 150);
            game->scene->addItem(msg);
            msg->setFlag(QGraphicsItem::ItemIsFocusable);
            msg->setFocus();
        }
        else if (checkNPC(aroundId)) {
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(leftChangePicture()));

            if (aroundId == 101) {
                // communicate
                communication * talk = new communication(game->maps->npcs[aroundId % 100]);
                setRedKey(getRedKey()+1);   // Give a red key
                game->updateInfo();
            }
            if (aroundId == 102) {
                // business
                business * businessman = new business(this, game);
            }
            if (aroundId == 103) {
                // mini game starts
                NPCFlyGame* npcfly = new NPCFlyGame();
            }
        }
        else if (checkMonster(aroundId)){
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(leftChangePicture()));

            if (checkWin(aroundId)) {
                // battle
                battle * battleMonster = new battle(game->maps->mons[getPosY()*11+getPosX()-1], this,getPosY()*11+getPosX()-1);

                // update information
               // game->updateInfo();

                // update Map
                //game->maps->updateMap(floor, getPosX()-1, getPosY(), 0);
                //delete game->maps->mons[getPosY()*11+getPosX()-1];
            }
            checkEnd(aroundId); // Ending test;
        }
        else if (checkDoor(aroundId)) {
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(leftChangePicture()));

            if (checkOpen(aroundId)) {
                // key number -1
                switch(aroundId) {
                case 4: setRedKey(getRedKey()-1); break;
                }

                game->maps->items[getPosY()*11+getPosX()-1]->openDoor();    // open door
                game->maps->updateMap(floor, getPosX()-1, getPosY(), 0);    // update map
                game->updateInfo();                                         // update info
            }
        }
        else if (checkUpstaris(aroundId)) {
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));

            // change floor
            floor++;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 97, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else if (checkDownstairs(aroundId)) {
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));

            // change floor
            floor--;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 96, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else {
            // show "walk"
            setPixmap(QPixmap::fromImage(hero_left2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(leftChangePicture()));
        }
    }

    // Key_Right
    else if (event->key() == Qt::Key_Right) {
        int aroundId = aroundInfo[3];
        if (checkWalkable(aroundId)){
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(rightChangePicture()));
            setPos(x()+40, y());
        }
        else if (checkPickable(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(rightChangePicture()));
            setPos(x()+40, y());

            // update map & delete item
            game->maps->updateMap(floor, getPosX(), getPosY(), 0);
            safeClearFloor();
            game->renderFloor(floor);

            // update item info
            updateItemInfo(aroundId);
            game->updateInfo();

            // show update message
            QString updateText;
            switch (aroundId) {
            case 301: updateText = "You get 3 ATKs !"; break;
            case 303: updateText = "You get Fly Floor Tools !"; game->backpackSys->addNewItem(303); break;
            case 304: updateText = "You get Monster Research Tools !"; game->backpackSys->addNewItem(304); break;
            }
            MsgBoard * msg = new MsgBoard(updateText, 100, 100, 440, 150);
            game->scene->addItem(msg);
            msg->setFlag(QGraphicsItem::ItemIsFocusable);
            msg->setFocus();
        }
        else if (checkNPC(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(rightChangePicture()));
            if (aroundId == 101) {
                // communicate
                communication * talk = new communication(game->maps->npcs[aroundId % 100]);
                setRedKey(getRedKey()+1);   // Give a red key
                game->updateInfo();
            }
            if (aroundId == 102) {
                // business
                business * businessman = new business(this, game);
            }
            if (aroundId == 103) {
                // mini game starts
                NPCFlyGame* npcfly = new NPCFlyGame();
            }
        }
        else if (checkMonster(aroundId)){
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(rightChangePicture()));
            if (checkWin(aroundId)) {
                // battle
                battle * battleMonster = new battle(game->maps->mons[getPosY()*11+getPosX()+1], this,getPosY()*11+getPosX()+1);

                // update information
           //     game->updateInfo();

                // update Map
             //   game->maps->updateMap(floor, getPosX()+1, getPosY(), 0);
               // delete game->maps->mons[getPosY()*11+getPosX()+1];
            }
            checkEnd(aroundId); // Ending test;
        }
        else if (checkDoor(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(rightChangePicture()));

            if (checkDoor(aroundId)) {
                // key number -1
                switch(aroundId) {
                case 4: setRedKey(getRedKey()-1); break;
                }

                game->maps->items[getPosY()*11+getPosX()+1]->openDoor();    // open door
                game->maps->updateMap(floor, getPosX()+1, getPosY(), 0);    // update map
                game->updateInfo();                                         // update info
            }
        }
        else if (checkUpstaris(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            // change floor
            floor++;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 97, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else if (checkDownstairs(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            // change floor
            floor--;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 96, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else {
            setPixmap(QPixmap::fromImage(hero_right2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(rightChangePicture()));
        }
    }

    // Key_Up
    else if (event->key() == Qt::Key_Up) {
        int aroundId = aroundInfo[0];
        qDebug() << aroundId;
        if (checkWalkable(aroundId)){
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(upChangePicture()));
            setPos(x(), y()-40);
        }
        else if (checkPickable(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(upChangePicture()));
            setPos(x(), y()-40);

            // update map & delete item
            game->maps->updateMap(floor, getPosX(), getPosY(), 0);
            safeClearFloor();
            game->renderFloor(floor);

            // update item info
            updateItemInfo(aroundId);
            game->updateInfo();

            // show update message
            QString updateText;
            switch (aroundId) {
            case 301: updateText = "You get 3 ATKs !"; break;
            case 303: updateText = "You get Fly Floor Tools !"; game->backpackSys->addNewItem(303); break;
            case 304: updateText = "You get Monster Research Tools !"; game->backpackSys->addNewItem(304); break;
            }
            MsgBoard * msg = new MsgBoard(updateText, 100, 100, 440, 150);
            game->scene->addItem(msg);
            msg->setFlag(QGraphicsItem::ItemIsFocusable);
            msg->setFocus();
        }
        else if (checkNPC(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(upChangePicture()));
            if (aroundId == 101) {
                // communicate
                communication * talk = new communication(game->maps->npcs[aroundId % 100]);
                setRedKey(getRedKey()+1);   // Give a red key
                game->updateInfo();
            }
            if (aroundId == 102) {
                // business
                business * businessman = new business(this, game);
            }
            if (aroundId == 103) {
                // mini game starts
                NPCFlyGame* npcfly = new NPCFlyGame();
            }
        }
        else if (checkMonster(aroundId)){
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(upChangePicture()));
            if (checkWin(aroundId)) {
                // battle
                battle * battleMonster = new battle(game->maps->mons[getPosY()*11-11+getPosX()], this,getPosY()*11-11+getPosX());

                // update information
              //  game->updateInfo();

                // update Map
                //game->maps->updateMap(floor, getPosX(), getPosY()-1, 0);
                //delete game->maps->mons[getPosY()*11-11+getPosX()];
            }
            checkEnd(aroundId); // Ending test;
        }
        else if (checkDoor(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(upChangePicture()));
            if (checkOpen(aroundId)){
                // key number -1
                switch(aroundId) {
                case 4: setRedKey(getRedKey()-1); break;
                }

                game->maps->items[getPosY()*11-11+getPosX()]->openDoor();   // open door
                game->maps->updateMap(floor, getPosX(), getPosY()-1, 0);    // update map
                game->updateInfo();                                         // update info
            }
        }
        else if (checkUpstaris(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            // change floor
            floor++;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 97, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else if (checkDownstairs(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            // change floor
            floor--;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 96, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else {
            setPixmap(QPixmap::fromImage(hero_up2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(upChangePicture()));
        }
    }

    // Key_Down
    else if (event->key() == Qt::Key_Down) {
        int aroundId = aroundInfo[1];
        if (checkWalkable(aroundId)){
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(downChangePicture()));
            setPos(x(), y()+40);
        }
        else if (checkPickable(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(downChangePicture()));
            setPos(x(), y()+40);

            // update map & delete item
            game->maps->updateMap(floor, getPosX(), getPosY(), 0);
            safeClearFloor();
            game->renderFloor(floor);

            // update item info
            updateItemInfo(aroundId);
            game->updateInfo();

            // show update message
            QString updateText;
            switch (aroundId) {
            case 301: updateText = "You get 3 ATKs !"; break;
            case 303: updateText = "You get Fly Floor Tools !"; game->backpackSys->addNewItem(303); break;
            case 304: updateText = "You get Monster Research Tools !"; game->backpackSys->addNewItem(304); break;
            }
            MsgBoard * msg = new MsgBoard(updateText, 100, 100, 440, 150);
            game->scene->addItem(msg);
            msg->setFlag(QGraphicsItem::ItemIsFocusable);
            msg->setFocus();
        }
        else if (checkNPC(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(downChangePicture()));
            if (aroundId == 101) {
                // communicate
                communication * talk = new communication(game->maps->npcs[aroundId % 100]);
                setRedKey(getRedKey()+1);   // Give a red key
                game->updateInfo();
            }
            if (aroundId == 102) {
                // business
                business * businessman = new business(this, game);
            }
            if (aroundId == 103) {
                // mini game starts

                NPCFlyGame* npcfly = new NPCFlyGame();
            }
        }
        else if (checkMonster(aroundId)){
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(downChangePicture()));
            if (checkWin(aroundId)) {
                // battle
                battle * battleMonster = new battle(game->maps->mons[getPosY()*11+11+getPosX()], this,getPosY()*11+11+getPosX());

                // update information
              //  game->updateInfo();

                // update Map
                //game->maps->updateMap(floor, getPosX(), getPosY()-1, 0);
                //delete game->maps->mons[getPosY()*11-11+getPosX()];
            }
            checkEnd(aroundId); // Ending test;
        }
        else if (checkDoor(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(downChangePicture()));

            if (checkDoor(aroundId)){
                // key number -1
                switch(aroundId) {
                case 4: setRedKey(getRedKey()-1); break;
                }

                game->maps->items[getPosY()*11+11+getPosX()]->openDoor();    // open door
                game->maps->updateMap(floor, getPosX(), getPosY()+1, 0);    // update map
                game->updateInfo();                                         // update info
            }
        }
        else if (checkUpstaris(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            // change floor
            floor++;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 97, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else if (checkDownstairs(aroundId)) {
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            // change floor
            floor--;
            floorVisitedNew(floor);
            safeClearFloor();
            game->renderFloor(floor);

            // change position
            int xPos,yPos;
            game->maps->findPosition(&xPos, &yPos, 96, floor);
            setPos(xPos*40+100, yPos*40);
            show();
            game->updateInfo();
        }
        else {
            setPixmap(QPixmap::fromImage(hero_down2_img.scaled(40, 40)));
            QTimer::singleShot(200, this, SLOT(downChangePicture()));
        }
    }


}

/*
 * Implementation notes: show()
 * ----------------------------
 * Draw the hero.
 */

void Hero::show()
{
    setPixmap(QPixmap::fromImage(hero_down1_img.scaled(40, 40)));   // draw the hero
}

/*
 * Implementation notes: getPosX(), getPosY()
 * ------------------------------------------
 * Return position of the hero on <code>Map2D</code>.
 */

int Hero::getPosX()
{
    return int((pos().x()-100) / 40);
}

int Hero::getPosY()
{
    return int(pos().y() / 40);
}

/*
 * Implementation notes: checkEnd()
 * --------------------------------
 * Check which end is finished.
 * TO DO: Ruturn enum-type.
 */

void Hero::checkEnd(int aroundID)
{
    // TO DO: multiple storylines check.
    // End 1
    if (aroundID == 203)
    {
        if (!checkWin(aroundID))
        {
            game->gameOver();
        }
        else {
            return;
        }
    }
}

/*
 * Implementation notes: checkX()
 * ------------------------------
 * Check whetehr the around ID is X.
 *
 * TO DO: use colliding test?
 *
 * QList<QGraphicsItem *> colliding = collidingItems();
 * for (int i = 0, n = colliding.size(); i < n; ++i) {
 *   if (typeid(*(colliding[i])) == typeid(Monster)) {
 *      return true;
 *   }
 * }
 *
 */

bool Hero::checkWalkable(int aroundID)
{
    if (aroundID == 0 | aroundID == 96 | aroundID ==97) {
        return true;
    }
    return false;
}

bool Hero::checkPickable(int aroundID)
{
    if (aroundID == 301 | aroundID == 303 |aroundID == 304) {
        return true;
    }
    return false;
}

bool Hero::checkNPC(int aroundID)
{
    if (aroundID == 101 | aroundID == 102  | aroundID == 103) {
        return true;
    }
    return false;
}

bool Hero::checkMonster(int aroundID)
{
    if (aroundID == 201 | aroundID == 202 | aroundID == 203) {
        return true;
    }
    return false;
}

bool Hero::checkDoor(int aroundID)
{
    if (aroundID == 4 | aroundID == 5) {
        return true;
    }
    return false;
}

bool Hero::checkUpstaris(int aroundID)
{
    if (aroundID == 6) {
        return true;
    }
    return false;
}

bool Hero::checkDownstairs(int aroundID)
{
    if (aroundID == 7) {
        return true;
    }
    return false;
}

/*
 * Implementation notes: checkOpen()
 * ---------------------------------
 * Check whether the door is able to open or not.
 */

bool Hero::checkOpen(int aroundID)
{
    switch(aroundID) {
    case 4: return (getRedKey()>0);
    case 5: return (game->maps->map2D[2][3][5] == 0);
    default: return false;
    }
}

/*
 * Implementation notes: checkWin()
 * ---------------------------------
 * Check whether the hero is stronger than the monster.
 */

bool Hero::checkWin(int aroundID)
{
    // get hp, atk, def
    Monster * monster = new Monster(aroundID);
    int monsterHp = monster->getHp();
    int monsterAtk = monster->getAtk();
    int monsterDef = monster->getDef();

    int heroHp = hp;
    int heroAtk = atk;
    int heroDef = def;

    int monsterHarm = max(0, monsterAtk-heroDef);
    int heroHarm = max(0, heroAtk-monsterDef);

    // judge

    int numOfRounds = monsterHp / heroHarm;
    //if (numOfRounds*monsterHarm >= heroHp) return false;
    if (monsterAtk>= heroDef &monsterDef>=heroAtk) return false;
    return true;
}

/*
 * Implementation notes: updateItemInfo()
 * --------------------------------------
 * After picking item, change corresponding information.
 */

void Hero::updateItemInfo(int aroundID)
{
    switch(aroundID) {
    case 301: atk += 3; break;
    case 303: monsterInfo = true; break;
    case 304: flyFloor = true; break;
    default: break;
    }
}

/*
 * Implementation notes: setFocusToSelf()
 * --------------------------------------
 * Set focus to Hero.
 */

void Hero::setFocusToSelf()
{
    this->setFocus();
}

/*
 * Implementation notes: getX()
 * ----------------------------
 * Get private hero information.
 */

int Hero::getHp()
{
    return hp;
}

int Hero::getAtk()
{
    return atk;
}

int Hero::getDef()
{
    return def;
}

int Hero::getLv()
{
    return lv;
}

int Hero::getMoney()
{
    return money;
}

int Hero::getExperience()
{
    return experience;
}

int Hero::getFloor()
{
    return floor;
}

int Hero::getRedKey()
{
    return redkey;
}

int Hero::getBlueKey()
{
    return bluekey;
}

int Hero::getYellowKey()
{
    return yellowkey;
}

bool Hero::getFlyFloor()
{
    return flyFloor;
}

bool Hero::getMonsterInfo()
{
    return monsterInfo;
}

/*
 * Implementation notes: setX()
 * ----------------------------
 * Set new value to private variables.
 */

void Hero::setHp(int newHp)
{
    hp = newHp;
}

void Hero::setAtk(int newAtk)
{
    atk = newAtk;
}

void Hero::setDef(int newDef)
{
    def = newDef;
}

void Hero::setMoney(int newMoney)
{
    money = newMoney;
}

void Hero::setLv(int newLv)
{
    lv = newLv;
}

void Hero::setExperience(int newExperience)
{
    experience = newExperience;

    // update lv automatically
    while (experience >= lv*80) {   // the experience required for each level lv is lv*80
        experience -= lv*80;
        lv++;
        atk += 5;
        def += 5;
        hp += 50;
    }
}

void Hero::setFloor(int newFloor)
{
    floor = newFloor;
}

void Hero::setRedKey(int newkey)
{
    redkey = newkey;
}

void Hero::setBlueKey(int newkey)
{
    bluekey = newkey;
}

void Hero::setYellowKey(int newkey)
{
    yellowkey = newkey;
}

bool Hero::checkFloorVisited(int floor)
{
    return floorVisited[floor];
}

/*
 * Implementation notes: XChangePicture()
 * --------------------------------------
 * Change picture of hero to show "walk".
 */

void Hero::upChangePicture()
{
    setPixmap(QPixmap::fromImage(hero_up1_img.scaled(40, 40)));
}

void Hero::downChangePicture()
{
    setPixmap(QPixmap::fromImage(hero_down1_img.scaled(40, 40)));
}

void Hero::leftChangePicture()
{
    setPixmap(QPixmap::fromImage(hero_left1_img.scaled(40, 40)));
}

void Hero::rightChangePicture()
{
    setPixmap(QPixmap::fromImage(hero_right1_img.scaled(40, 40)));
}

/*
 * Implementation notes: getAroundId()
 * -----------------------------------
 * Get ID of around positions.
 */

void Hero::getAroundId()
{
    int posX = getPosX();
    int posY = getPosY();

    // up
    if (posY == 0) {
        aroundInfo[0] = 1;
    }
    else {
        aroundInfo[0] = game->maps->map2D[floor][posY-1][posX];
    }

    // down
    if (posY == 10) {
        aroundInfo[1] = 1;
    }
    else {
        aroundInfo[1] = game->maps->map2D[floor][posY+1][posX];
    }

    // left
    if (posX == 0) {
        aroundInfo[2] = 1;
    }
    else {
        aroundInfo[2] = game->maps->map2D[floor][posY][posX-1];
    }

    // right
    if (posX == 10) {
        aroundInfo[3] = 1;
    }
    else {
        aroundInfo[3] = game->maps->map2D[floor][posY][posX+1];
    }
}

/*
 * Implementation notes: floorVisitedNew()
 * -------------------------------------------------------------
 * Judge whether the new floor is visited before, if not, then add
 * it to the list.
 */

void Hero::floorVisitedNew(int floorID)
{
    if (!checkFloorVisited(floorID)) {
        floorVisited[floorID] = true;
    }
}

/*
 * Implementation notes: safeClearFloor()
 * --------------------------------------
 * Clear all items except hero.
 */

void Hero::safeClearFloor() {
    QList<QGraphicsItem*> all = game->scene->items();
    qDebug() << all.size();
    for (int i = 0; i < all.size(); i++) {
        if (typeid(*(all[i])) == typeid(unwalkable)) {
            scene()->removeItem(all[i]);
            delete all[i];
        }
        else if (typeid(*(all[i])) == typeid(Monster)) {
            scene()->removeItem(all[i]);
            delete all[i];
        }
        else if (typeid(*(all[i])) == typeid(NPC)) {
            scene()->removeItem(all[i]);
        }
        else if (typeid(*(all[i])) == typeid(Item)) {
            scene()->removeItem(all[i]);
            delete all[i];
        }
    }
}
