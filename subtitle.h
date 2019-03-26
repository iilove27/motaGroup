/*
 * File: subtitle.h
 * ----------------
 * This file exports a class <code>subtitle</code>, which is able to show
 * subtitle and move automatically.
 */

#ifndef SUBTITLE_H
#define SUBTITLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QKeyEvent>

class subtitle: public QObject, public QGraphicsRectItem
{   Q_OBJECT
public:
    // constructor
    subtitle(QString content, QGraphicsItem* parent=nullptr);

    // public mehtods
    void keyPressEvent(QKeyEvent* event);
public slots:
    void textMove();

private:
    // private variables
    QGraphicsTextItem *text;
    int distance;
    QTimer *timer;
};

#endif // SUBTITLE_H
