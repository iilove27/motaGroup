#ifndef CHOICERECT_H
#define CHOICERECT_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QFileInfo>
#include <QGraphicsPixmapItem>

class ChoiceRect: public QObject, public QGraphicsRectItem
{   Q_OBJECT

public:
    ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem* parent=nullptr,
               int gapX = 0, int gapY = 0, bool isBattle = false, bool isbackpack = false, bool recordChoice=false);
    void keyPressEvent(QKeyEvent * event);
    int chosen;
    int getCurrentChoice();
    bool canMove;
    void setCurrentChoice(int setter);
signals:
    void spacePressed();

private:
    int numChoice;
    int currentChoice;
    bool horizontal, privateisBattle, privateisbackpack;
    int privategapX, privategapY;
    bool privaterecordChoice;
    QGraphicsPixmapItem * yulan;
    bool yulanExist = false;

};

#endif // CHOICERECT_H
