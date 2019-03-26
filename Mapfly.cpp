#include "Mapfly.h"
#include "Game.h"
#include <QDebug>


extern Game* game;

MapFly::MapFly()
{
    qDebug() << 1;
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
    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = 220;
    double byPos = 400;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);

    // add Item button
    for (int floor_i = 0; floor_i < floorButton.size(); floor_i++) {
        byPos = floor_i*40;
        floorButton[floor_i]->setPos(bxPos, byPos);
        game->scene->addItem(floorButton[floor_i]);
        // connect
        qsignal[floor_i]->setMapping(floorButton[floor_i], floorButton[floor_i]->getButtonText().toInt());
        connect(floorButton[floor_i], SIGNAL(clicked()), qsignal[floor_i], SLOT(map()));
        connect(qsignal[floor_i], SIGNAL(mapped(int)), this, SLOT(fly(int)));
    }
}

void MapFly::back()
{
    game->scene->removeItem(floorFrame);
    game->scene->removeItem(backButton);
    for (int floor_i = 0; floor_i < floorButton.size(); floor_i++) {
        game->scene->removeItem(floorButton[floor_i]);
    }

    game->hero->setFocusToSelf();
}

void MapFly::fly(int floorID)
{
    qDebug() << 1;
    // change floor
    game->hero->setFloor(floorID);
    game->hero->safeClearFloor();
    game->renderFloor(floorID);

    qDebug() << 2;
    // change position
    int xPos,yPos;
    game->maps->findPosition(&xPos, &yPos, 97, floorID);
    game->hero->setPos(xPos*40+100, yPos*40);
    game->hero->show();
    game->updateInfo();

    qDebug() << 3;
    // TO DO: bug
    qDebug() << "what happened???";
    game->scene->removeItem(floorFrame);
    game->scene->removeItem(backButton);
    for (int floor_i = 0; floor_i < floorButton.size(); floor_i++) {
        game->scene->removeItem(floorButton[floor_i]);
    }
    delete floorFrame;
    delete backButton;

    qDebug() << 4;

    game->hero->setFocusToSelf();
    // delete this;
}

