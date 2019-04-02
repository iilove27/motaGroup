#ifndef MONSTERINFO_H
#define MONSTERINFO_H

#include <QObject>
#include "Button.h"
#include "Game.h"

extern Game* game;

class monsterInfo: public QObject
{   Q_OBJECT
public:
    // constructor
    monsterInfo();

    // public methods
    void showFrame();
    void findMonster();
    bool checkRepeated(int monsterID);
public slots:
    void back();

private:
    QQueue<int> monsterID;
    QQueue<QGraphicsTextItem*> hpInfo, atkInfo, defInfo, expInfo, moneyInfo;
    QQueue<QString> imagePath;
    QQueue<QGraphicsPixmapItem*> monsterImage;
    QGraphicsRectItem* monsterFrame;
    Button* backButton;

};

#endif // MONSTERINFO_H

