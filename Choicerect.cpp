#include "Choicerect.h"
#include <QKeyEvent>


ChoiceRect::ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem *parent): QGraphicsRectItem (parent)
{
    numChoice = numOfChoice;
    currentChoice = 0;
    horizontal = horizontalChoice;
    setRect(0, 0, sizeX, sizeY); // position(0,0) & size(200,40)
    QBrush brush;
    brush.setStyle(Qt::Dense5Pattern);
    brush.setColor(Qt::lightGray);
    setBrush(brush);
}

void ChoiceRect::keyPressEvent(QKeyEvent *event)
{
    if (horizontal) {
        if ((event->key() == Qt::Key_Left) && (currentChoice != 0)) {
            this->setPos(this->x()-160, this->y());
            currentChoice--;
        }

        if ((event->key() == Qt::Key_Right) && (currentChoice != numChoice-1)) {
            this->setPos(this->x()+160, this->y());
            currentChoice++;
        }
    }

    else {
        if ((event->key() == Qt::Key_Up) && (currentChoice != 0)) {
            this->setPos(this->x(), this->y()+40);
            currentChoice--;
        }

        if ((event->key() == Qt::Key_Down) && (currentChoice != numChoice-1)) {
            this->setPos(this->x(), this->y()-40);
            currentChoice++;
        }
    }



}
