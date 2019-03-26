#ifndef BACKPACK_H
#define BACKPACK_H

#include <QObject>
#include <QQueue>
#include "Button.h"
#include "Hero.h"

class backpack: public QObject
{   Q_OBJECT
public:
    // constructor
    backpack();

    // public methods
    void showFrame();
    void addNewItem(int itemID);
    QString getNameOfItem(int itemID);
public slots:
    // void showButton();
    void back();
    void flyFloor();
private:
    // private variables
    QQueue<Button*> itemButton;
    QGraphicsRectItem* backpackFrame;
    Button* backButton;
};

#endif // BACKPACK_H
