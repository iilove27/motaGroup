/*
 * File: unwalkable.h
 * ------------------
 * This file exports class <code>unwalkable</code>.
 * Instance:
 *      <code>wall</code>
 *      <code>specialArea</code>
 */

#ifndef UNWALKABLE_H
#define UNWALKABLE_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QString>
#include <QObject>

class unwalkable: public QObject, public QGraphicsPixmapItem
{   Q_OBJECT
public:
    // constructor
    unwalkable(int unwalkableID, QGraphicsItem* parent=nullptr);

    // public method
    void show();
    int getId();
public slots:
    void changePicture();

private:
    // private parameter
    int id;
    int count;
    QString image1;
    QString image2;
};

#endif // UNWALKABLE_H
