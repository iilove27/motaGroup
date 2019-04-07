/*
 * File: Msgboard.h
 * ----------------
 * This file exports class <code>MsgBoard</code>, which would show what
 * hero get and disappear automatically after a while.
 */

#ifndef MSGBOARD_H
#define MSGBOARD_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QObject>
#include "Hero.h"

class MsgBoard: public QObject, public QGraphicsRectItem
{   Q_OBJECT
public:
    // constructor
    MsgBoard(QString text, int x, int y, int width, int height, QGraphicsItem* parent=nullptr);
public slots:
    void deleteAndFocusBack();
    void justDelete();

private:
    // private variable
    QGraphicsTextItem* text;
};

#endif // MSGBOARD_H
