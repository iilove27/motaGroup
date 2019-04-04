#ifndef CHOICERECT_H
#define CHOICERECT_H

#include <QGraphicsRectItem>
#include <QBrush>

class ChoiceRect: public QObject, public QGraphicsRectItem
{   Q_OBJECT

public:
    ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem* parent=nullptr,
               int gapX = 0, int gapY = 0, bool isBattle = false, bool isbackpack = false);
    void keyPressEvent(QKeyEvent * event);
    int chosen;
    int getCurrentChoice();

signals:
    void spacePressed();

private:
    int numChoice;
    int currentChoice;
    bool horizontal, privateisBattle, privateisbackpack;
    int privategapX, privategapY;
};

#endif // CHOICERECT_H
