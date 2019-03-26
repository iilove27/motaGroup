/*
 * File: battle.cpp
 * ----------------
 * This file implements battle.h interface.
 */

#include "battle.h"
using namespace std;

extern Game *game;

battle::battle(Monster * monster, Hero * hero)
{
    // if (!checkBattle()) delete this;     // bug

    // get Monster hp & atk & def
    monsterId = monster->getId();
    monsterHp = monster->getHp();
    monsterAtk = monster->getAtk();
    monsterDef = monster->getDef();
    monsterHpInfo = "HP:\t" + QString::number(monsterHp);
    monsterAtkInfo = "ATK:\t" + QString::number(monsterAtk);
    monsterDefInfo = "DEF:\t" + QString::number(monsterDef);

    // get Hero hp & atk & def
    heroHp = hero->getHp();
    heroAtk = hero->getAtk();
    heroDef = hero->getDef();
    heroHpInfo = "HP:\t" + QString::number(heroHp);
    heroAtkInfo = "ATK:\t" + QString::number(heroAtk);
    heroDefInfo = "DEF:\t" + QString::number(heroDef);

    // get harm value (>=0)
    monsterHarm = max(0, monsterAtk-heroDef);
    heroHarm = max(0, heroAtk-monsterDef);

    battleFrameShow(monster, hero); // show battle frame
}

/*
 * Implementation notes: battleFrameShow(Monster* monster, Hero* hero)
 * ---------------------------------------------------------------------
 * This function creates a <code>battleFrame</code> and displays information
 * relevant to battle.
 */

void battle::battleFrameShow(Monster * monster, Hero * hero)
{
    // create battle frame
    battleFrame = new QGraphicsRectItem();
    battleFrame->setRect(100, 50, 440, 220);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    battleFrame->setBrush(brush);
    game->scene->addItem(battleFrame);
    battleFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    battleFrame->setFocus();

    // create battle information & image
    monsterHpText = new QGraphicsTextItem(monsterHpInfo);
    monsterAtkText = new QGraphicsTextItem(monsterAtkInfo);
    monsterDefText = new QGraphicsTextItem(monsterDefInfo);
    monsterHpText->setPos(200,50);
    monsterAtkText->setPos(200,100);
    monsterDefText->setPos(200,150);

    heroHpText = new QGraphicsTextItem(heroHpInfo);
    heroAtkText = new QGraphicsTextItem(heroAtkInfo);
    heroDefText = new QGraphicsTextItem(heroDefInfo);
    heroHpText->setPos(330,50);
    heroAtkText->setPos(330,100);
    heroDefText->setPos(330,150);

    game->scene->addItem(monsterHpText);
    game->scene->addItem(monsterAtkText);
    game->scene->addItem(monsterDefText);
    game->scene->addItem(heroHpText);
    game->scene->addItem(heroAtkText);
    game->scene->addItem(heroDefText);

    // add monster & hero image to battle frame
    hero_img_battle = new QGraphicsPixmapItem();
    QString hero_img_path = ":/images/down1.png";
    QImage hero_img;
    hero_img.load(hero_img_path);
    QPixmap hero_pic = QPixmap::fromImage(hero_img.scaled(80, 80));
    hero_img_battle->setPixmap(hero_pic);
    hero_img_battle->setPos(450,80);
    game->scene->addItem(hero_img_battle);

    monster_img_battle = new QGraphicsPixmapItem();
    QString monster_img_path = QString(":/images/") + QString::number(monsterId) + QString(".png");
    QImage monster_img;
    monster_img.load(monster_img_path);
    QPixmap monster_pic = QPixmap::fromImage(monster_img.scaled(80, 80));
    monster_img_battle->setPixmap(monster_pic);
    monster_img_battle->setPos(110,80);
    game->scene->addItem(monster_img_battle);

    // TO DO: add name to battle frame

    // battle
    timer = new QTimer(this);
    timer->start(300);
    connect(timer,SIGNAL(timeout()),this,SLOT(battleOnce()));

    // update information
    hero->setHp(heroHp);
    hero->setMoney(hero->getMoney()+monster->getMoney());
    hero->setExperience(hero->getExperience()+monster->getExperience());
    game->updateInfo();

    hero->setFocusToSelf(); // focus back
}

/*
 * Implementation notes: checkBattle(Monster* monster, Hero* hero)
 * ---------------------------------------------------------------
 * Check whether hero is stronger than monster. Only hp, atk & def would
 * be considered.
 */

bool battle::checkBattle()
{
    int numOfRounds = monsterHp / heroHarm;
    if (numOfRounds*monsterHarm >= heroHp) return false;
    return true;
}

/*
 * Implemenetation notes: updateText()
 * -----------------------------------
 * Upate HP text after every round of battle.
 */

void battle::updateText()
{
    monsterHpInfo = "HP:\t" + QString::number(monsterHp);
    heroHpInfo = "HP:\t" + QString::number(heroHp);
    monsterHpText->setPlainText(monsterHpInfo);
    heroHpText->setPlainText(heroHpInfo);
}

/*
 * Implementation notes: battleOnce()
 * ----------------------------------
 * If <code>monsterHp</code> is no smaller than 0, battle once;
 * otherwise, delete the battle frame. <code>timer</code> should
 * be stopped, or it would continue all the time.
 */

void battle::battleOnce()
{
    monsterHp -= heroHarm;
    if (monsterHp <= 0)
    {
        monsterHp = 0;
        updateText();
        game->scene->removeItem(battleFrame);
        game->scene->removeItem(monsterHpText);
        game->scene->removeItem(monsterAtkText);
        game->scene->removeItem(monsterDefText);
        game->scene->removeItem(heroHpText);
        game->scene->removeItem(heroAtkText);
        game->scene->removeItem(heroDefText);
        game->scene->removeItem(hero_img_battle);
        game->scene->removeItem(monster_img_battle);
        timer->stop();  // stop timer
    }
    updateText();
    heroHp -= monsterHarm;
    updateText();
}
