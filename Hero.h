#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>


class Hero: public QGraphicsPixmapItem{
public:
    Hero(QGraphicsItem * parent=0);
    void init();
    void keyPressEvent(QKeyEvent * event);
    void getMonsInfo(QKeyEvent *event);
    bool checkEncounter();
    void show();
    int getPosX();
    int getPosY();
    bool checkEnd();

public slots:
    void setFocusToSelf();

private:
    int hp,lv,atk,def,money,experience,redkey,bluekey,yellowkey,special;
    int floor;
    int aroundInfo[4];
    void getAroundId();
};

#endif // MYRECT_H
