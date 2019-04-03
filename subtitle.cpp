/*
 * File: subtitle.cpp
 * ----------------
 * This file implements subtitle.h interface.
 */

#include "subtitle.h"
#include <QTimer>
#include "Game.h"
using namespace std;

extern Game * game;

subtitle::subtitle(QString content, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // create subtitle frame
    setRect(100, 0, 440, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);
    game->scene->addItem(this);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // draw the text & skip
    distance = 400;
    text = new QGraphicsTextItem(content);
    text->setPos(200,distance);
    game->scene->addItem(text);

    QGraphicsTextItem * skipText = new QGraphicsTextItem("- space -");
    skipText->setPos(440, 400);
    qDebug() << "aaa";
    game->scene->addItem(skipText);

    // subtitle move
    timer = new QTimer(this);
    timer->start(5);
    connect(timer,SIGNAL(timeout()),this,SLOT(textMove()));
}

/*
 * Implementation notes: keyPressEvent(QKeyEvent* event)
 * -----------------------------------------------------
 * Use Key_Space to skip and start game.
 */

void subtitle::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        game->scene->removeItem(this);
        delete this;
        game->start();
    }
}

/*
 * Implemenetation notes: textMove()
 * ---------------------------------
 * Move text and -50 is set to stop moving and start game.
 */

void subtitle::textMove()
{
    // TO DO: try to use "QPropertyAnimation"
    if (distance >= -50)    // set -50 to stop (based on text length)
    {
        distance = distance - 1;
        text->setPos(200, distance);
        return;
    }
    game->scene->removeItem(this);
    delete this;
    game->start();

}
