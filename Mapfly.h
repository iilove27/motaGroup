#ifndef MAPFLY_H
#define MAPFLY_H

#include <QObject>
#include <QQueue>
#include <QSignalMapper>
#include "Button.h"
#include "Hero.h"

class MapFly: public QObject
{   Q_OBJECT
public:
    // constructor
    MapFly();

public slots:
    void showFrame();
    void back();
    void fly(int floorID);
private:
    // private variables
    QQueue<Button*> floorButton;
    QQueue<QSignalMapper*> qsignal;
    QGraphicsRectItem* floorFrame;
    Button* backButton;
};

#endif // MAPFLY_H
