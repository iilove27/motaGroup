/*
 * File: backpack.cpp
 * ----------------
 * This file implements backpack.h interface.
 */

#include "backpack.h"
#include "monsterinfo.h"
#include "Game.h"
#include <QDebug>

extern Game* game;

backpack::backpack()
{

}

/*
 * Implementation notes: showFrame()
 * ---------------------------------
 * Draw the backpack frame.
 */

void backpack::showFrame()
{
    // create frame
    backpackFrame = new QGraphicsRectItem();
    backpackFrame->setRect(220, 0, 200, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    backpackFrame->setBrush(brush);
    game->scene->addItem(backpackFrame);
    backpackFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    backpackFrame->setFocus();
    qDebug() << backpackFrame;

    // add BACK button
    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = 220;
    double byPos = 400;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);

    // add Item button
    for (int item_i = 0; item_i < itemButton.size(); item_i++) {
        byPos = item_i*40;
        itemButton[item_i]->setPos(bxPos, byPos);
        game->scene->addItem(itemButton[item_i]);

        // connect
    }
}

void backpack::addNewItem(int itemID)
{
    itemButton.enqueue(new Button(getNameOfItem(itemID), 200, 40));
    if (itemButton.last()->getButtonText() == QString("FLY FLOOR")) {
        connect(itemButton.last(), SIGNAL(clicked()), this, SLOT(flyFloor()));
    }
    else if (itemButton.last()->getButtonText() == QString("MONSTER SEARCH")) {
        connect(itemButton.last(), SIGNAL(clicked()), this, SLOT(searchMonster()));
    }
}

QString backpack::getNameOfItem(int itemID)
{
    switch(itemID) {
    case 303: return QString("FLY FLOOR");
    case 304: return QString("MONSTER SEARCH");
    default: return QString("???");
    }
}

void backpack::back()
{
    game->scene->removeItem(backpackFrame);
    game->scene->removeItem(backButton);
    for (int item_i = 0; item_i < itemButton.size(); item_i++) {
        game->scene->removeItem(itemButton[item_i]);
    }
    game->hero->setFocusToSelf();
}

void backpack::flyFloor()
{
    game->scene->removeItem(backpackFrame);
    game->scene->removeItem(backButton);
    for (int item_i = 0; item_i < itemButton.size(); item_i++) {
        game->scene->removeItem(itemButton[item_i]);
    }

    MapFly* mapfly = new MapFly();
    mapfly->showFrame();
}

void backpack::searchMonster()
{
    game->scene->removeItem(backpackFrame);
    game->scene->removeItem(backButton);
    for (int item_i = 0; item_i < itemButton.size(); item_i++) {
        game->scene->removeItem(itemButton[item_i]);
    }

    monsterInfo* monsterinfo = new monsterInfo();
    monsterinfo->showFrame();
}

