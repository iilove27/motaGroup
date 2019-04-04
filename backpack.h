#ifndef BACKPACK_H
#define BACKPACK_H

#include <QObject>
#include <QQueue>
#include "Button.h"
#include "Hero.h"
#include "Mapfly.h"

class backpack: public QObject
{   Q_OBJECT
public:
    // constructor
    backpack();

    // public methods
    void showFrame();
    void addNewItem(int itemID);
    QString getNameOfItem(int itemID);
    std::map<Button*, int> buttonMap;
public slots:
    // void showButton();
    void back();
    void flyFloor();
    void searchMonster();
    void buttonChosen();

private:
    // private variables
    QQueue<Button*> itemButton;
    QGraphicsRectItem* backpackFrame;
    Button* backButton;
    ChoiceRect* choiceRect;
};

#endif // BACKPACK_H
