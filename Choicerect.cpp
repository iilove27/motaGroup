#include "Choicerect.h"
#include <QKeyEvent>
#include <iostream>
#include "Game.h"
#include <QDebug>

extern Game* game;
ChoiceRect::ChoiceRect(int sizeX, int sizeY, int numOfChoice, bool horizontalChoice, QGraphicsItem *parent,
                       int gapX, int gapY, bool isBattle, bool isbackpack, bool recordChoice): QGraphicsRectItem (parent)
{
    privaterecordChoice = recordChoice;
    canMove = true;
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
    if (canMove) {
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

                if (privaterecordChoice){

                    /*
                    if (currentChoice == 0){
                        qDebug()<<"thi is a record button 0"<<endl;
                        QString screenShotPath;
                        screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot1.png";
                        if (QFileInfo(screenShotPath).exists()==false){
                            screenShotPath="/Users/chenxuanyu212/CPPcode/motaGroup/far.png";
                        }
                        QImage image(screenShotPath);

                        yulan = new QGraphicsPixmapItem(QPixmap::fromImage(image.scaled(60,60,Qt::KeepAspectRatioByExpanding)));
                        game->scene->addItem(yulan);

                        if (event->key() == Qt::Key_Down){

                            screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot2.png";
                            if (QFileInfo(screenShotPath).exists()==false){
                                qDebug()<<"mei cun tu"<<endl;
                                screenShotPath="/Users/chenxuanyu212/CPPcode/motaGroup/far.jpg";
                            }

                            QImage image(screenShotPath);
                            yulan = new QGraphicsPixmapItem(QPixmap::fromImage(image.scaled(60,60,Qt::KeepAspectRatioByExpanding)));
                            game->scene->addItem(yulan);

                            this->setPos(this->x(), this->y()+privategapY);
                            currentChoice++;
                        }
                    }
                    */
                    if ((event->key() == Qt::Key_Up) && (currentChoice != 0)) {
                        QString screenShotPath;
                        switch(currentChoice){
                        case 1: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot1.png";
                                break;
                        case 2: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot2.png";
                                break;
                        case 3: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot3.png";
                                break;
                        case 4: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot4.png";
                                break;
                        case 5: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot5.png";
                                break;
                        }
                        qDebug()<<"thi is a record button"<<currentChoice+1<<endl;
                        if (QFileInfo(screenShotPath).exists()==false){
                            qDebug()<<"mei cun tu"<<endl;
                            screenShotPath=":/images/far.jpg";
                        }

                        QImage image(screenShotPath);
                        if (yulanExist) {
                            game->scene->removeItem(yulan);
                            yulanExist = false;
                        }

                        yulan = new QGraphicsPixmapItem(QPixmap::fromImage(image.scaled(120,120,Qt::KeepAspectRatioByExpanding)));
                        game->scene->addItem(yulan);
                        yulanExist = true;

                        this->setPos(this->x(), this->y()-privategapY);
                        currentChoice--;
                    }
                    else if ((event->key() == Qt::Key_Down) && (currentChoice != 5)) {
                        QString screenShotPath;
                        switch(currentChoice){
                        case 0: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot2.png";
                                break;
                        case 1: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot3.png";
                                break;
                        case 2: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot4.png";
                                break;
                        case 3: screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot5.png";
                                break;
                        case 4: screenShotPath = "Back button";
                                break;
                        }
                        qDebug()<<"thi is a record button"<<currentChoice+1<<endl;

                        if (screenShotPath == "Back button"){
                            game->scene->removeItem(yulan);
                            yulanExist = false;
                            this->setPos(this->x(), this->y()+privategapY);
                            currentChoice++;
                        }
                        else {
                            if (QFileInfo(screenShotPath).exists()==false){
                                qDebug()<<"mei cun tu"<<endl;
                                screenShotPath=":/images/far.jpg";
                            }

                            QImage image(screenShotPath);
                            if (yulanExist) {
                                game->scene->removeItem(yulan);
                                yulanExist = false;
                            }
                            yulan = new QGraphicsPixmapItem(QPixmap::fromImage(image.scaled(120,120,Qt::KeepAspectRatioByExpanding)));

                            game->scene->addItem(yulan);
                            yulanExist = true;
                            this->setPos(this->x(), this->y()+privategapY);
                            currentChoice++;
                        }
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

void ChoiceRect::setCurrentChoice(int setter)
{
    currentChoice = setter;
}
