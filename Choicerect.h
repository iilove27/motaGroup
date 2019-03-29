#ifndef CHOICERECT_H
#define CHOICERECT_H

#include <QGraphicsRectItem>
#include <QBrush>

class ChoiceRect: public QObject, public QGraphicsRectItem
{   Q_OBJECT

public:
    ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem* parent=nullptr);
    void keyPressEvent(QKeyEvent * event);

private:
    int numChoice;
    int currentChoice;
    bool horizontal;
};

#endif // CHOICERECT_H
