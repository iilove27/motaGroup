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
#include "recordbutton.h"
#include <QFile>
#include <QFileInfo>

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
private:
    // private variables
    QGraphicsRectItem *recordFrame;
    QGraphicsTextItem *recordText;
    ChoiceRect* choiceRect;

    //Button *saveButton1, *saveButton2, *saveButton3, *saveButton4, *saveButton5, *backButton;
    //RecordButton *recordButton1, *recordButton2, *recordButton3, *recordButton4, *recordButton5;
    Button *recordButton1, *recordButton2, *recordButton3, *recordButton4, *recordButton5,*backButton;

};

#endif // SAVELOAD_H
