/*
 * File: communication.h
 * ---------------------
 * This file exports a class <code>communication</code>. Users are allow to
 * use <code>Key_Space</code> to continue communication or use Mouse to click
 * to choose conversation content, which is mainly part of multiple storylines.
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QBrush>
#include <QKeyEvent>
#include <QQueue>
#include <QObject>
#include "npc.h"
#include "Button.h"
#include "Choicerect.h"

class communication: public QObject, public QGraphicsRectItem
{   Q_OBJECT
public:
    // constructor
    communication(NPC* npc, QGraphicsItem* parent=nullptr);

    // public methods
    void keyPressEvent(QKeyEvent* event);
    bool checkOption(QString sentence);
    std::map<Button*, int> showButton101();   // show button when communicate with NPC(id=101)
    void showChoiceInit(int x, int y);
    std::map<Button*, int> buttonMap;
    void show(QString sentence);

public slots:
    void addText10101();    // add different content
    void addText10102();
    void addText10103();
    void buttonChosen();



private:
    // private variable
    int id;
    int imageid;
    QQueue<QString> communicationText,nameText;

    QGraphicsTextItem* text, *nameofNPC;
    Button* buttonOption1,* buttonOption2,* buttonOption3;
    ChoiceRect* choiceRect;
    QString image;
    QGraphicsPixmapItem* BIG_img;
};

#endif // COMMUNICATION_H
