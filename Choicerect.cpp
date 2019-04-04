#include "Choicerect.h"
#include <QKeyEvent>
#include <iostream>


ChoiceRect::ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem *parent,
                       int gapX, int gapY, bool isBattle, bool isbackpack): QGraphicsRectItem (parent)
{
    privateisbackpack = isbackpack;
    privategapX = gapX;
    privategapY = gapY;
    chosen = -1;
    numChoice = numOfChoice;
    currentChoice = 0;
    horizontal = horizontalChoice;
    privateisBattle = isBattle;
    setRect(0, 0, sizeX, sizeY); // position(0,0) & size(200,40)
    QColor opaqueCyan = Qt::cyan;
    opaqueCyan.setAlphaF(0.3);
    setBrush(opaqueCyan);


}

void ChoiceRect::keyPressEvent(QKeyEvent *event)
{
    // battle 比较特殊，是2x2分布的choice，其他的选择全都是一条线分布（hopefully）。
    if (privateisBattle) {
        std::cout << currentChoice << std::endl;
        if (currentChoice == 0) {
            if (event->key() == Qt::Key_Down) {
                this->setPos(this->x(), this->y()+privategapY);
                currentChoice += 2;
            }
            if (event->key() == Qt::Key_Right) {
                this->setPos(this->x()+privategapX, this->y());
                currentChoice++;
            }

        }

        else if (currentChoice == 1) {
            if (event->key() == Qt::Key_Down) {
                this->setPos(this->x(), this->y()+privategapY);
                currentChoice += 2;
            }
            if (event->key() == Qt::Key_Left) {
                this->setPos(this->x()-privategapX, this->y());
                currentChoice--;
            }

        }

        else if (currentChoice == 2) {
            if (event->key() == Qt::Key_Up) {
                this->setPos(this->x(), this->y()-privategapY);
                currentChoice -= 2;
            }
            if (event->key() == Qt::Key_Right) {
                this->setPos(this->x()+privategapX, this->y());
                currentChoice++;
            }

        }

        else if (currentChoice == 3) {
            if (event->key() == Qt::Key_Up) {
                this->setPos(this->x(), this->y()-privategapY);
                currentChoice -= 2;
            }
            if (event->key() == Qt::Key_Left) {
                this->setPos(this->x()-privategapX, this->y());
                currentChoice--;
            }

        }
    }
    else if (privateisbackpack) {


        if ((event->key() == Qt::Key_Down) && (currentChoice != numChoice-1)) {
            if (currentChoice == numChoice-2) {
                this->setPos(this->x(), 400);
                currentChoice = numChoice - 1;

            }
            else {
                this->setPos(this->x(), this->y()+privategapY);
                currentChoice++;
            }

        }

        if ((event->key() == Qt::Key_Up) && (currentChoice != 0)) {
            if (currentChoice == numChoice-1) {
                this->setPos(this->x(), privategapY*(numChoice-2));
                currentChoice--;
            }
            else {
                this->setPos(this->x(), this->y()-privategapY);
                currentChoice--;
            }
        }
    }

    else {
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

    }

    if (event->key() == Qt::Key_Space) {
        chosen = currentChoice;
        emit spacePressed();
        std::cout << "space pressed" << std::endl;
    }



}

int ChoiceRect::getCurrentChoice()
{
    std::cout << currentChoice;
    return currentChoice;
}
