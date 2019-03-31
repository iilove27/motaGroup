/*
 * File: business.cpp
 * ----------------
 * This file implements business.h interface.
 */

#include "business.h"
#include <iostream>

using namespace std;

business::business(Hero * hero, Game * game)
{
    // set Add Value
    hpAddValue = 100;
    atkAddValue = 5;
    defAddValue = 5;
    expAddValue = 100;

    // create frame
    businessFrame = new QGraphicsRectItem();
    businessFrame->setRect(100, 0, 440, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    businessFrame->setBrush(brush);
    game->scene->addItem(businessFrame);
    businessFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    businessFrame->setFocus();

    // draw the text
    businessText = new QGraphicsTextItem(QString("If you have $50, you could buy following things:"));
    QFont titleFont("comic sans", 10);
    businessText->setFont(titleFont);
    double txPos = game->width()/2 - businessText->boundingRect().width()/2;
    double tyPos = 100;
    businessText->setPos(txPos, tyPos);
    game->scene->addItem(businessText);

    // Add HP button
    addHPButton = new Button(QString("HP +100"), 200, 40);
    double hxPos = game->width()/2 - businessText->boundingRect().width()/2+50;
    double hyPos = 150;
    addHPButton->setPos(hxPos, hyPos);
    connect(addHPButton, SIGNAL(clicked()), this, SLOT(addHp()));
    game->scene->addItem(addHPButton);
    buttonMap.insert(std::pair<Button*, int> (addHPButton, 0));

    // Add ATK button
    addATKButton = new Button(QString("ATK +5"), 200, 40);
    double axPos = game->width()/2 - businessText->boundingRect().width()/2+50;
    double ayPos = 200;
    addATKButton->setPos(axPos, ayPos);
    connect(addATKButton, SIGNAL(clicked()), this, SLOT(addATK()));
    game->scene->addItem(addATKButton);
    buttonMap.insert(std::pair<Button*, int> (addATKButton, 1));


    // Add DEF button
    addDEFButton = new Button(QString("DEF +5"), 200, 40);
    double dxPos = game->width()/2 - businessText->boundingRect().width()/2+50;
    double dyPos = 250;
    addDEFButton->setPos(dxPos, dyPos);
    connect(addDEFButton, SIGNAL(clicked()), this, SLOT(addDEF()));
    game->scene->addItem(addDEFButton);
    buttonMap.insert(std::pair<Button*, int> (addDEFButton, 2));


    // Add EXP button
    addEXPButton = new Button(QString("EXP +100"), 200, 40);
    double exPos = game->width()/2 - businessText->boundingRect().width()/2+50;
    double eyPos = 300;
    addEXPButton->setPos(exPos, eyPos);
    connect(addEXPButton, SIGNAL(clicked()), this, SLOT(addEXP()));
    game->scene->addItem(addEXPButton);
    buttonMap.insert(std::pair<Button*, int> (addEXPButton, 3));


    // Add BACK button
    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = game->width()/2 - businessText->boundingRect().width()/2+50;
    double byPos = 350;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);
    buttonMap.insert(std::pair<Button*, int> (backButton, 4));

    choiceRect = new ChoiceRect(200, 40, 5, false, nullptr, 0, 50);
    choiceRect->setPos(hxPos, hyPos);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();

}

/*
 * Implementation notes: addX()
 * ----------------------------
 * Check whether hero has enough money and update information if money
 * is enough.
 */

void business::addHp()
{
    if (game->hero->getMoney() >= 50)
    {
        game->hero->setMoney(game->hero->getMoney()-50);
        game->hero->setHp(game->hero->getHp()+100);
        game->updateInfo();
    }
}

void business::addATK()
{
    if (game->hero->getMoney() >= 50)
    {
        game->hero->setMoney(game->hero->getMoney()-50);
        game->hero->setAtk(game->hero->getAtk()+5);
        game->updateInfo();
    }
}

void business::addDEF()
{
    if (game->hero->getMoney() >= 50)
    {
        game->hero->setMoney(game->hero->getMoney()-50);
        game->hero->setDef(game->hero->getDef()+5);
        game->updateInfo();
    }
}

void business::addEXP()
{
    if (game->hero->getMoney() >= 50)
    {
        game->hero->setMoney(game->hero->getMoney()-50);
        game->hero->setExperience(game->hero->getExperience()+100);
        game->updateInfo();
    }
}

/*
 * Implementation notes: back()
 * ----------------------------
 * Remove all Items on the business frame and frame. Then set focus
 * back to hero.
 */

void business::back()
{
    game->scene->removeItem(businessFrame);
    game->scene->removeItem(businessText);
    game->scene->removeItem(addHPButton);
    game->scene->removeItem(addATKButton);
    game->scene->removeItem(addDEFButton);
    game->scene->removeItem(addEXPButton);
    game->scene->removeItem(backButton);
    game->scene->removeItem(choiceRect);
    // delete this

    game->hero->setFocusToSelf();
}

void business::buttonChosen()
{
    cout << "Enter buttonChosen function" << endl;
    int currentChoice = choiceRect->chosen;
    cout << currentChoice;
    std::map<Button*, int>::iterator it;
    for (it = buttonMap.begin(); it != buttonMap.end(); it++) {
        if (it->second == currentChoice) {
            it->first->chosen();
        }
    }
}
