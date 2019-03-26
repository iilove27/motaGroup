/*
 * File: Item.h
 * --------------
 * This file exports a class <code>Item</code>.
 * Instance:
 *      <code>redJewel</code>
 *      <code>blueJewel</code>
 *      <code>healthPots</code>
 *      <code>redKey</code>
 *      <code>blueKey</code>
 *      <code>yellowKey</code>
 *      <code>sword</code>
 *      <code>shield</code>
 *      <code>searchMonster</code>
 *      <code>flyFloor</code>
 */

#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Item: public QObject, public QGraphicsPixmapItem
{   Q_OBJECT
public:
    // constructor
    Item(int itemID, QGraphicsItem * parent=nullptr);

    // public methods
    void openDoor();
    void show();
    int getId();
public slots:
    void changePictureFirst();
    void changePictureSecond();
    void changePictureThird();
    void changePictureFourth();

private:
    // private variable
    int id;
};

#endif // ITEM_H
