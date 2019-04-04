#ifndef MAPFLY_H
#define MAPFLY_H

#include <QObject>
#include <QQueue>
#include <QSignalMapper>
#include "Button.h"
#include "Hero.h"
#include "Choicerect.h"

class MapFly: public QObject
{   Q_OBJECT
public:
    // constructor
    MapFly();
    std::map<Button*, int> buttonMap;

public slots:
    void showFrame();
    void back();
    void fly(int floorID);
    void buttonChosen();
private:
    // private variables
    QQueue<Button*> floorButton;
    QQueue<QSignalMapper*> qsignal;
    QGraphicsRectItem* floorFrame;
    Button* backButton;
    ChoiceRect* choiceRect;
};

#endif // MAPFLY_H
