#include "Choicerect.h"
#include <QKeyEvent>
#include <iostream>


ChoiceRect::ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem *parent,
                       int gapX, int gapY): QGraphicsRectItem (parent)
{
    privategapX = gapX;
    privategapY = gapY;
    chosen = -1;
    numChoice = numOfChoice;
    currentChoice = 0;
    horizontal = horizontalChoice;
    setRect(0, 0, sizeX, sizeY); // position(0,0) & size(200,40)
    QColor opaqueCyan = Qt::cyan;
    opaqueCyan.setAlphaF(0.3);
    setBrush(opaqueCyan);
}

void ChoiceRect::keyPressEvent(QKeyEvent *event)
{
    if (horizontal) {
        if ((event->key() == Qt::Key_Left) && (currentChoice != 0)) {
            this->setPos(this->x()-privategapX, this->y());
            currentChoice--;
        }

        if ((event->key() == Qt::Key_Right) && (currentChoice != numChoice-1)) {
            this->setPos(this->x()+privategapX, this->y());
            currentChoice++;
        }
    }

    else {
        if ((event->key() == Qt::Key_Up) && (currentChoice != 0)) {
            this->setPos(this->x(), this->y()-privategapY);
            currentChoice--;
        }

        if ((event->key() == Qt::Key_Down) && (currentChoice != numChoice-1)) {
            this->setPos(this->x(), this->y()+privategapY);
            currentChoice++;
        }
    }

    if (event->key() == Qt::Key_Space) {
        chosen = currentChoice;
        emit spacePressed();
    }



}

int ChoiceRect::getCurrentChoice()
{
    std::cout << currentChoice;
    return currentChoice;
}
