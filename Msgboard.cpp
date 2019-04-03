/*
 * File: Msgboard.cpp
 * ------------------
 * This file implements Msgboard.h interface.
 */

#include "Msgboard.h"
#include "Game.h"
#include <unistd.h>
#include <QDebug>
#include <QTimer>

extern Game* game;

MsgBoard::MsgBoard(QString name, int x, int y, int width, int height, QGraphicsItem* parent): QGraphicsRectItem (parent)
{
    // draw the message board
    setRect(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // TO DO: set focus to avoid mis-operate?

    // draw the text
    text = new QGraphicsTextItem(name, this);
    text->setPos(150,150);

    QTimer::singleShot(600, this, SLOT(deleteAndFocusBack()));  // remove after 400
}

/*
 * Implementation notes: deleteAndFocusBack()
 * ------------------------------------------
 * Delete message box and focus back to hero.
 */

void MsgBoard::deleteAndFocusBack()
{
    // delete
    game->scene->removeItem(this);
    delete this;

    // focus back
    game->hero->setFocusToSelf();
}
