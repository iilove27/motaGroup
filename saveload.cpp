/*
 * File: saveload.cpp
 * ----------------
 * This file implements saveload.h interface.
 */

#include "saveload.h"
#include "Game.h"
#include "Msgboard.h"
#include <fstream>

extern Game * game;

SaveLoad::SaveLoad()
{
    // create frame
    recordFrame = new QGraphicsRectItem();
    recordFrame->setRect(100, 0, 440, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    recordFrame->setBrush(brush);
    game->scene->addItem(recordFrame);
    recordFrame->setFlag(QGraphicsItem::ItemIsFocusable);
    recordFrame->setFocus();
}

/*
 * Implementation notes: showSaveRecord(), showLoadRecord(), showLoadRecordOnMainMenu()
 * ------------------------------------------------------------------------------------
 * Show button on the frame and connect to different functions. QSignalMapper is used in
 * this case to pass parameters.
 */

void SaveLoad::showSaveRecord()
{
    // draw the text
    recordText = new QGraphicsTextItem(QString("Choose which record you want to save"));
    QFont titleFont("comic sans", 10);
    recordText->setFont(titleFont);
    double txPos = game->width()/2 - recordText->boundingRect().width()/2;
    double tyPos = 70;
    recordText->setPos(txPos, tyPos);
    game->scene->addItem(recordText);

    // draw record1 button
    recordButton1 = new Button(QString("Record 1"), 200, 40);
    double hxPos1 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos1 = 120;
    recordButton1->setPos(hxPos1, hyPos1);
    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    signalMapper1->setMapping(recordButton1, 1);
    connect(recordButton1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    connect(signalMapper1, SIGNAL(mapped(int)), this, SLOT(save(int)));
    game->scene->addItem(recordButton1);

    // draw record2 button
    recordButton2 = new Button(QString("Record 2"), 200, 40);
    double hxPos2 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos2 = 170;
    recordButton2->setPos(hxPos2, hyPos2);
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    signalMapper2->setMapping(recordButton2, 2);
    connect(recordButton2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(save(int)));
    game->scene->addItem(recordButton2);

    // draw record3 button
    recordButton3 = new Button(QString("Record 3"), 200, 40);
    double hxPos3 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos3 = 220;
    recordButton3->setPos(hxPos3, hyPos3);
    QSignalMapper *signalMapper3 = new QSignalMapper(this);
    signalMapper3->setMapping(recordButton3, 3);
    connect(recordButton3, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    connect(signalMapper3, SIGNAL(mapped(int)), this, SLOT(save(int)));
    game->scene->addItem(recordButton3);

    // Add record4 button
    recordButton4 = new Button(QString("Record 4"), 200, 40);
    double hxPos4 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos4 = 270;
    recordButton4->setPos(hxPos4, hyPos4);
    QSignalMapper *signalMapper4 = new QSignalMapper(this);
    signalMapper4->setMapping(recordButton4, 4);
    connect(recordButton4, SIGNAL(clicked()), signalMapper4, SLOT(map()));
    connect(signalMapper4, SIGNAL(mapped(int)), this, SLOT(save(int)));
    game->scene->addItem(recordButton4);

    // draw record5 button
    recordButton5 = new Button(QString("Record 5"), 200, 40);
    double hxPos5 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos5 = 320;
    recordButton5->setPos(hxPos5, hyPos5);
    QSignalMapper *signalMapper5 = new QSignalMapper(this);
    signalMapper5->setMapping(recordButton5, 5);
    connect(recordButton5, SIGNAL(clicked()), signalMapper5, SLOT(map()));
    connect(signalMapper5, SIGNAL(mapped(int)), this, SLOT(save(int)));
    game->scene->addItem(recordButton5);

    // draw back button
    backButton = new Button(QString("Back"), 200, 40);
    double bxPos = game->width()/2 - recordText->boundingRect().width()/2;
    double byPos = 370;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);
}


void SaveLoad::showLoadRecord()
{
    // draw the text
    recordText = new QGraphicsTextItem(QString("Choose which record you want to load"));
    QFont titleFont("comic sans", 10);
    recordText->setFont(titleFont);
    double txPos = game->width()/2 - recordText->boundingRect().width()/2;
    double tyPos = 70;
    recordText->setPos(txPos, tyPos);
    game->scene->addItem(recordText);

    // draw record1 button
    recordButton1 = new Button(QString("Record 1"), 200, 40);
    double hxPos1 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos1 = 120;
    recordButton1->setPos(hxPos1, hyPos1);
    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    signalMapper1->setMapping(recordButton1, 1);
    connect(recordButton1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    connect(signalMapper1, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton1);

    // draw record2 button
    recordButton2 = new Button(QString("Record 2"), 200, 40);
    double hxPos2 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos2 = 170;
    recordButton2->setPos(hxPos2, hyPos2);
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    signalMapper2->setMapping(recordButton2, 2);
    connect(recordButton2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton2);

    // draw record3 button
    recordButton3 = new Button(QString("Record 3"), 200, 40);
    double hxPos3 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos3 = 220;
    recordButton3->setPos(hxPos3, hyPos3);
    QSignalMapper *signalMapper3 = new QSignalMapper(this);
    signalMapper3->setMapping(recordButton3, 3);
    connect(recordButton3, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    connect(signalMapper3, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton3);

    // Add record4 button
    recordButton4 = new Button(QString("Record 4"), 200, 40);
    double hxPos4 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos4 = 270;
    recordButton4->setPos(hxPos4, hyPos4);
    QSignalMapper *signalMapper4 = new QSignalMapper(this);
    signalMapper4->setMapping(recordButton4, 4);
    connect(recordButton4, SIGNAL(clicked()), signalMapper4, SLOT(map()));
    connect(signalMapper4, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton4);

    // draw record5 button
    recordButton5 = new Button(QString("Record 5"), 200, 40);
    double hxPos5 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos5 = 320;
    recordButton5->setPos(hxPos5, hyPos5);
    QSignalMapper *signalMapper5 = new QSignalMapper(this);
    signalMapper5->setMapping(recordButton5, 5);
    connect(recordButton5, SIGNAL(clicked()), signalMapper5, SLOT(map()));
    connect(signalMapper5, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton5);

    // draw back button
    backButton = new Button(QString("Back"), 200, 40);
    double bxPos = game->width()/2 - recordText->boundingRect().width()/2;
    double byPos = 370;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);
}

void SaveLoad::showLoadRecordOnMainMenu()
{
    // draw the text
    recordText = new QGraphicsTextItem(QString("Choose which record you want to load"));
    QFont titleFont("comic sans", 10);
    recordText->setFont(titleFont);
    double txPos = game->width()/2 - recordText->boundingRect().width()/2;
    double tyPos = 70;
    recordText->setPos(txPos, tyPos);
    game->scene->addItem(recordText);

    // draw record1 button
    recordButton1 = new Button(QString("Record 1"), 200, 40);
    double hxPos1 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos1 = 120;
    recordButton1->setPos(hxPos1, hyPos1);
    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    signalMapper1->setMapping(recordButton1, 1);
    connect(recordButton1, SIGNAL(clicked()), signalMapper1, SLOT(map()));
    connect(signalMapper1, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton1);

    // draw record2 button
    recordButton2 = new Button(QString("Record 2"), 200, 40);
    double hxPos2 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos2 = 170;
    recordButton2->setPos(hxPos2, hyPos2);
    QSignalMapper *signalMapper2 = new QSignalMapper(this);
    signalMapper2->setMapping(recordButton2, 2);
    connect(recordButton2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
    connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton2);

    // draw record3 button
    recordButton3 = new Button(QString("Record 3"), 200, 40);
    double hxPos3 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos3 = 220;
    recordButton3->setPos(hxPos3, hyPos3);
    QSignalMapper *signalMapper3 = new QSignalMapper(this);
    signalMapper3->setMapping(recordButton3, 3);
    connect(recordButton3, SIGNAL(clicked()), signalMapper3, SLOT(map()));
    connect(signalMapper3, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton3);

    // Add record4 button
    recordButton4 = new Button(QString("Record 4"), 200, 40);
    double hxPos4 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos4 = 270;
    recordButton4->setPos(hxPos4, hyPos4);
    QSignalMapper *signalMapper4 = new QSignalMapper(this);
    signalMapper4->setMapping(recordButton4, 4);
    connect(recordButton4, SIGNAL(clicked()), signalMapper4, SLOT(map()));
    connect(signalMapper4, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton4);

    // draw record5 button
    recordButton5 = new Button(QString("Record 5"), 200, 40);
    double hxPos5 = game->width()/2 - recordText->boundingRect().width()/2;
    double hyPos5 = 320;
    recordButton5->setPos(hxPos5, hyPos5);
    QSignalMapper *signalMapper5 = new QSignalMapper(this);
    signalMapper5->setMapping(recordButton5, 5);
    connect(recordButton5, SIGNAL(clicked()), signalMapper5, SLOT(map()));
    connect(signalMapper5, SIGNAL(mapped(int)), this, SLOT(load(int)));
    game->scene->addItem(recordButton5);

    // draw back button
    backButton = new Button(QString("Back"), 200, 40);
    double bxPos = game->width()/2 - recordText->boundingRect().width()/2;
    double byPos = 370;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backMainMenu()));
    game->scene->addItem(backButton);
}

/*
 * Implementation notes: save(), load()
 * ------------------------------------
 * Save into file and load from file.
 */

void SaveLoad::save(int recordNum)
{
    QString showText = "Save successfully";
    string fileInfoName;
    string fileMapName;

    //  TO DO: use relative path
    switch (recordNum)
    {
    case 1: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord1.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord1.dat";
            break;
    case 2: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord2.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord2.dat";
            break;
    case 3: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord3.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord3.dat";
            break;
    case 4: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord4.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord4.dat";
            break;
    case 5: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord5.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord5.dat";
            break;
    }

    fstream  saveFile;
    saveFile.open(fileInfoName, ios::out|ios::trunc);
    game->maps->saveMapintoRecord(fileMapName); // save map matrix into file

    // hp,atk,def,lv,money,exp,floor,posX,poxY,redkey,yellowkey,bluekey
    saveFile<< game->hero->getHp()<<endl;
    saveFile<< game->hero->getAtk()<<endl;
    saveFile<< game->hero->getDef()<<endl;
    saveFile<< game->hero->getLv()<<endl;
    saveFile<< game->hero->getMoney()<<endl;
    saveFile<< game->hero->getExperience()<<endl;
    saveFile<< game->hero->getFloor()<<endl;
    saveFile<< game->hero->getPosX()<<endl;
    saveFile<< game->hero->getPosY()<<endl;
    saveFile<< game->hero->getRedKey()<<endl;
    saveFile<< game->hero->getYellowKey()<<endl;
    saveFile<< game->hero->getBlueKey()<<endl;
    saveFile.close();

    MsgBoard * msg = new MsgBoard(showText, 100, 100, 440, 150);
    game->scene->addItem(msg);
}

void SaveLoad::load(int recordNum)
{
    fstream loadFile;
    string fileInfoName, fileMapName;

    //  TO DO: use relative path
    switch (recordNum)
    {
    case 1: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord1.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord1.dat";
            break;
    case 2: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord2.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord2.dat";
            break;
    case 3: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord3.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord3.dat";
            break;
    case 4: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord4.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord4.dat";
            break;
    case 5: fileInfoName = "/Users/haroldxu/motaGroup/InfoRecord5.dat";
            fileMapName = "/Users/haroldxu/motaGroup/MapRecord5.dat";
            break;
    }

    // order: hp,atk,def,lv,money,exp,floor,posX,poxY,redkey,yellowkey,bluekey
    loadFile.open(fileInfoName, ios::in);

    int new_heroHp;
    int new_heroAtk;
    int new_heroDef;
    int new_heroLv;
    int new_heroMoney;
    int new_heroExp;
    int new_heroFloor;
    int new_heroPosX;
    int new_heroPosY;
    int new_redKey;
    int new_yellowKey;
    int new_blueKey;

    loadFile>>new_heroHp;
    loadFile>>new_heroAtk;
    loadFile>>new_heroDef;
    loadFile>>new_heroLv;
    loadFile>>new_heroMoney;
    loadFile>>new_heroExp;
    loadFile>>new_heroFloor;
    loadFile>>new_heroPosX;
    loadFile>>new_heroPosY;
    loadFile>>new_redKey;
    loadFile>>new_yellowKey;
    loadFile>>new_blueKey;
    loadFile.close();

    // clear
    game->scene->clear();

    // draw the map
    game->maps = new Map(fileMapName);
    game->maps->show(new_heroFloor);  // Initial Render

    // draw the hero
    game->hero = new Hero();
    game->hero->setPos(100+40*new_heroPosX, 40*new_heroPosY); // Initial Position
    game->hero->show();
    game->scene->addItem(game->hero);
    game->hero->setFlag(QGraphicsItem::ItemIsFocusable);

    game->hero->setHp(new_heroHp);
    game->hero->setAtk(new_heroAtk);
    game->hero->setDef(new_heroDef);
    game->hero->setLv(new_heroLv);
    game->hero->setMoney(new_heroMoney);
    game->hero->setExperience(new_heroExp);
    game->hero->setFloor(new_heroFloor);
    game->hero->setRedKey(new_redKey);
    game->hero->setBlueKey(new_blueKey);
    game->hero->setYellowKey(new_yellowKey);

    // draw the information
    game->drawGUI();

    // add BGM
    // TO DO: use Button to control BGM
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgm.mp3"));
    music->play();

    game->hero->setFocus();
    game->show();
}

/*
 * Implementation notes: back(), backMainMenu()
 * --------------------------------------------
 * <code>back</code> would return to floor and focus back to hero.
 * <code>backMainMenu</code> would return to main menu.
 */

void SaveLoad::back()
{
    game->scene->removeItem(recordFrame);
    game->scene->removeItem(recordText);
    game->scene->removeItem(recordButton1);
    game->scene->removeItem(recordButton2);
    game->scene->removeItem(recordButton3);
    game->scene->removeItem(recordButton4);
    game->scene->removeItem(recordButton5);
    game->scene->removeItem(backButton);
    // delete this;

    game->hero->setFocusToSelf();   // focus back to hero
}

void SaveLoad::backMainMenu()
{
    // only remove items since hero is not created on main menu
    game->scene->removeItem(recordFrame);
    game->scene->removeItem(recordText);
    game->scene->removeItem(recordButton1);
    game->scene->removeItem(recordButton2);
    game->scene->removeItem(recordButton3);
    game->scene->removeItem(recordButton4);
    game->scene->removeItem(recordButton5);
    game->scene->removeItem(backButton);
    // delete this;
}
