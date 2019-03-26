/*
 * File: business.h
 * ----------------
 * This file exports a class <code>business</code>. Business frame would
 * include several <code>Button</code>. Mouse event would be realized first,
 * key Event would be considered later.
 * Things could be bought from businessman(each costs $50):
 *      HP  +100
 *      ATK +5
 *      DEF +5
 *      EXP +100
 * TO Do: you would get a random key after you have consumed $100 with
 * [90% nothing, 9% yellow key, 0.9% blue key, 0.1% red key].
 */

#ifndef BUSINESS_H
#define BUSINESS_H

#include <QObject>
#include "Button.h"
#include "Hero.h"
#include "Game.h"

extern Game* game;

class business: public QObject
{   Q_OBJECT
public:
    // constructor
    business(Hero* hero, Game* game);
public slots:
    void addHp();
    void addATK();
    void addDEF();
    void addEXP();
    void back();

private:
    // private variables
    int hpAddValue, atkAddValue, defAddValue, expAddValue;

    Button* addHPButton,* addATKButton,* addDEFButton,* addEXPButton,* backButton;
    QGraphicsRectItem* businessFrame;
    QGraphicsTextItem* businessText;
};

#endif // BUSINESS_H
