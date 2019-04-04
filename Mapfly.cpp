#include "Mapfly.h"
#include "Game.h"
#include <QDebug>
#include <iostream>

extern Game* game;

MapFly::MapFly()
{
    for (int floor_i=0; floor_i<4; floor_i++) {
        if (game->hero->checkFloorVisited(floor_i)) {
            floorButton.enqueue(new Button(QString::number(floor_i), 200, 40));
            qsignal.enqueue(new QSignalMapper(this));
        }
    }
}

void MapFly::showFrame()
{
    // create frame
    floorFrame = new QGraphicsRectItem();
    floorFrame->setRect(220, 0, 200, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    floorFrame->setBrush(brush);
    game->scene->addItem(floorFrame);
    floorFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    floorFrame->setFocus();

    // add BACK button
    buttonMap.clear();
    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = 220;
    double byPos = 400;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);
    std::cout << floorButton.size();
    buttonMap.insert(std::pair<Button*, int> (backButton, floorButton.size()));

    // add Item button
    for (int floor_i = 0; floor_i < floorButton.size(); floor_i++) {
        byPos = floor_i*40;
        floorButton[floor_i]->setPos(bxPos, byPos);
        buttonMap.insert(std::pair<Button*, int> (floorButton[floor_i], floor_i));
        game->scene->addItem(floorButton[floor_i]);
        // connect
        qsignal[floor_i]->setMapping(floorButton[floor_i], floorButton[floor_i]->getButtonText().toInt());
        connect(floorButton[floor_i], SIGNAL(clicked()), qsignal[floor_i], SLOT(map()));
        connect(qsignal[floor_i], SIGNAL(mapped(int)), this, SLOT(fly(int)));
    }
    choiceRect = new ChoiceRect(200, 40, floorButton.size()+1, true, nullptr, 0, 40, false, true);
    choiceRect->setPos(220, 0);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();


}

void MapFly::back()
{
    game->scene->removeItem(choiceRect);
    game->scene->removeItem(floorFrame);
    game->scene->removeItem(backButton);
    for (int floor_i = 0; floor_i < floorButton.size(); floor_i++) {
        game->scene->removeItem(floorButton[floor_i]);
    }

    game->hero->setFocusToSelf();
}

void MapFly::fly(int floorID)
{
    // change floor
    game->hero->setFloor(floorID);
    game->hero->safeClearFloor();
    game->renderFloor(floorID);

    // change position
    int xPos,yPos;
    game->maps->findPosition(&xPos, &yPos, 97, floorID);
    game->hero->setPos(xPos*40+100, yPos*40);
    game->hero->show();
    game->updateInfo();

    game->scene->removeItem(choiceRect);
    game->scene->removeItem(floorFrame);
    game->scene->removeItem(backButton);
    for (int floor_i = 0; floor_i < floorButton.size(); floor_i++) {
        game->scene->removeItem(floorButton[floor_i]);
    }

    game->hero->setFocusToSelf();
    // delete this;
}

void MapFly::buttonChosen()
{
    std::cout << "Enter buttonChosen function" << std::endl;
    int currentChoice = choiceRect->chosen;
    std::cout << currentChoice;
    std::map<Button*, int>::iterator it;
    for (it = buttonMap.begin(); it != buttonMap.end(); it++) {
        if (it->second == currentChoice) {
            std::cout << "found" << it->second;
            it->first->chosen();
        }
    }
}


