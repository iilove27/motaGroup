/*
 * File: saveload.h
 * ----------------
 * This file exports the function of <code>save</code> and <code>load</code> in
 * the class <code>SaveLoad</code>.
 */

#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <QObject>
#include <QSignalMapper>
#include "Button.h"
#include "Hero.h"
#include "Game.h"
#include <QFile>
#include <QFileInfo>
#include <QString>


extern Game * game;

class SaveLoad: public QObject
{   Q_OBJECT
public:
    // constructor
    SaveLoad();
    std::map<Button*, int> buttonMap;
public slots:
    void showSaveRecord();
    void showLoadRecord();
    void showLoadRecordOnMainMenu();
    void save(int recordNum);
    void load(int recordNum);
    void back();
    void backMainMenu();
    void buttonChosen();
    void deleteMsgAndText();
private:
    // private variables
    QGraphicsRectItem *recordFrame,*msg;
    QGraphicsTextItem *recordText,*text;
    ChoiceRect* choiceRect;
    Button *recordButton1, *recordButton2, *recordButton3, *recordButton4, *recordButton5,*backButton;

};

#endif // SAVELOAD_H
