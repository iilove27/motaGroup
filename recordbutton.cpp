/*
 * File: Button.cpp
 * --------------------
 * This file implements Button.h interface.
 */

#include "recordbutton.h"
#include <iostream>
#include "Game.h"
#include <QFileInfo>
#include <QFile>
extern Game*game;

RecordButton::RecordButton(QString name, int sizeX, int sizeY, QGraphicsItem* parent): QGraphicsRectItem (parent)
{
    // draw the button frame
    buttonID = 1874; // 随便数
    setRect(0, 0, sizeX, sizeY); // position(0,0) & size(200,40)
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // draw the text
    textContent = name;
    text = new QGraphicsTextItem(textContent, this);
    double xPos = rect().width()/2 - text->boundingRect().width()/2;
    double yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    // set hover event
    setAcceptHoverEvents(true);
}

/*
 * Implementation notes: mousePressEvent()
 * -------------------------------
 * Send <code>clicked()</code> signal and connect.
 * Use to start, load, close, restart, skip, back, set BGM.
 */

void RecordButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);    // change color & style
    emit clicked();
}

void RecordButton::chosen()
{
    emit clicked();
}

/*
 * Implementation notes: hoverEnterEvent, hoverLeaveEvent
 * ------------------------------------------------
 * Change color whether mouse hover over the button or not.
 */

void RecordButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    QString screenShotPath;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);    // change color & style
    /*
    switch (recordNum)
    {

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
    */

    if (QFileInfo(screenShotPath).exists()==false){
        screenShotPath="/Users/chenxuanyu212/CPPcode/motaGroup/far.png";
    }
    screenShotPath = "/Users/chenxuanyu212/CPPcode/motaGroup/screenshot1.png";
    QImage image(screenShotPath);

    yulan = new QGraphicsPixmapItem(QPixmap::fromImage(image.scaled(20,20,Qt::KeepAspectRatioByExpanding)));
    game->scene->addItem(yulan);


}

void RecordButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);    // change color & style
    game->scene->removeItem(yulan);
}

/*
 * Implementation notes: setButtonText(QString textContent)
 * --------------------------------------------------------
 * Change text content on the <code>Button</code>.
 */

void RecordButton::setButtonText(QString textContent)
{
    text->setPlainText(textContent);
    double xPos = rect().width()/2 - text->boundingRect().width()/2;
    double yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);
}

/*
 * Implementation notes: getButtonText()
 * -------------------------------------
 * Return name on the Button.
 */

QString RecordButton::getButtonText()
{
    return textContent;
}

std::vector<int> RecordButton::getButtonPos()
{
    std::vector<int> pos;
    pos.push_back(int(this->x()));
    pos.push_back(int(this->y()));
    return pos;
}

int RecordButton::getButtonID()
{
    return buttonID;
}
