/*
 * File: Game.cpp
 * --------------------
 * This file implements Game.h interface.
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QBrush>
#include <QImage>
#include <stdlib.h>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QTimer>
#include <errno.h>
#include <QFile>
#include <QTextStream>
#include "Game.h"
#include "Hero.h"
#include "Monster.h"
#include "Button.h"
#include "Unwalkable.h"
#include "npc.h"
#include "subtitle.h"
#include "saveload.h"
using namespace std;

Game::Game(QWidget* parent)
{
    // set the scene & background
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,440+100*2,440);
    setBackgroundBrush(QBrush(QImage(":/images/bg.png").scaled(440+100*2, 440)));
    setScene(scene);
    setFixedSize(640,440);
}

/*
 * Implementation notes: subtitleMove()
 * ------------------------------------
 * Clear main menu and show subtitle. Choose <code>skip</code> to skip.
 */

void Game::subtitleMove()
{
    // clear
    scene->clear();

    // subtitle Move
    QString subtitleContent = "offer收割🐔陈教授🐂🍺！\n"\
                              "陈教授真的太强了，强无敌！！！\n"\
                              "陈教授怎么会这么强 其他人真的都是弟弟\n"\
                              "所以陈教授进入这个地方是干嘛？？？";
    subtitle* beginSubtitle = new subtitle(subtitleContent);
}

/*
 * Implementation notes: start() / restartGame()
 * -----------------------------
 * Start the game and initialize the information.
 */

void Game::start()
{
    scene->clear(); // clear

    // new backpack
    backpackSys = new backpack();

    // draw the map
    maps = new Map("/Users/haroldxu/Desktop/mota/map.dat"); // TO DO: use relative path
    maps->show(0);                                          // initial render & show floor 0

    // draw the hero
    hero = new Hero();
    hero -> setPos(300, 400); // Initial Position
    hero->show();
    scene->addItem(hero);
    hero ->setFlag(QGraphicsItem::ItemIsFocusable);

    drawGUI();  // draw the information

    // add BGM
    // TO DO: use Button to control BGM
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgm.mp3"));
    music->play();

    hero->setFocus();   // set focus to Hero
    show();             // show game
}

void Game::restartGame()
{
    start();
}

/*
 * Implementation notes: drawPanel(int x, int y, int width, int height, QColor color, double opacity)
 * --------------------------------------------------------------------------------------------------
 * Draw the background of information window.
 */

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    // draw the panel
    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}



/*
 * Implementation notes: displayMainMenu()
 * -------------------------------
 * Main menu includes three Buttons:
 *      <code>Play</code>
 *      <code>Load</code>
 *      <code>Quit</code>
 */

void Game::displayMainMenu()
{
    // show game title
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Magic Tower"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    double txPos = this->width()/2 - titleText->boundingRect().width()/2;
    double tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    // Play button
    Button* playButton = new Button(QString("Play"), 200, 40);
    double bxPos = this->width()/2 - titleText->boundingRect().width()/2+50;
    double byPos = 250;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(subtitleMove()));
    scene->addItem(playButton);

    // Load button
    Button* loadButton = new Button(QString("Load"), 200, 40);
    double lxPos = this->width()/2 - titleText->boundingRect().width()/2+50;
    double lyPos = 300;
    loadButton->setPos(lxPos, lyPos);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(showLoadOnMainMenu()));
    scene->addItem(loadButton);

    // Quit button
    Button* quitButton = new Button(QString("Quit"), 200, 40);
    double qxPos = this->width()/2 - titleText->boundingRect().width()/2+50;
    double qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

/*
 * Implementation notes: drawGUI()
 * -------------------------------
 * Draw the information about item and hero.
 */

void Game::drawGUI()
{
    // left side about hero information
    drawPanel(0, 0, 100, 440, Qt::darkCyan, 1);

    QGraphicsTextItem* HeroInfo = new QGraphicsTextItem(QString("Hero"));
    HeroInfo->setPos(25, 0);
    scene->addItem(HeroInfo);

    lvText = new QGraphicsTextItem(QString("Lv :\t") + QString::number(hero->getLv()));
    hpText = new QGraphicsTextItem(QString("HP :\t") + QString::number(hero->getHp()));
    atkText = new QGraphicsTextItem(QString("Attack :\t") + QString::number(hero->getAtk()));
    defText = new QGraphicsTextItem(QString("Defence :\t") + QString::number(hero->getDef()));
    expText = new QGraphicsTextItem(QString("Exp :\t") + QString::number(hero->getExperience()));
    moneyText = new QGraphicsTextItem(QString("Money :\t") + QString::number(hero->getMoney()));
    floorText = new QGraphicsTextItem(QString("Floor :\t") + QString::number(hero->getFloor()));

    lvText->setPos(0, 40);
    hpText->setPos(0, 80);
    atkText->setPos(0, 120);
    defText->setPos(0, 160);
    expText->setPos(0, 200);
    moneyText->setPos(0, 240);
    floorText->setPos(0, 280);

    scene->addItem(lvText);
    scene->addItem(hpText);
    scene->addItem(atkText);
    scene->addItem(defText);
    scene->addItem(expText);
    scene->addItem(moneyText);
    scene->addItem(floorText);

    // right side about item information
    drawPanel(540, 0, 100, 440, Qt::darkCyan, 1);

    QGraphicsTextItem* OtherInfo = new QGraphicsTextItem(QString("Item"));
    OtherInfo->setPos(540, 0);
    scene->addItem(OtherInfo);

    yellowKeyText = new QGraphicsTextItem(QString("Yellow key :\t") + QString::number(hero->getYellowKey()));
    blueKeyText = new QGraphicsTextItem(QString("Blue key :\t") + QString::number(hero->getBlueKey()));
    redKeyText = new QGraphicsTextItem(QString("Red key :\t") + QString::number(hero->getRedKey()));

    yellowKeyText->setPos(540, 40);
    blueKeyText->setPos(540, 80);
    redKeyText->setPos(540, 120);

    scene->addItem(yellowKeyText);
    scene->addItem(blueKeyText);
    scene->addItem(redKeyText);

    // if special tool is obtained, show how to use
    // TO DO: special functions for tools
    if (hero->getFloor() == true) {
        floorFlyText = new QGraphicsTextItem(QString("Fly :\t") + QString("Press F"));
        floorFlyText->setPos(540, 160);
        scene->addItem(floorFlyText);
    }
    if (hero->getMonsterInfo() == true) {
        monsterSearchText = new QGraphicsTextItem(QString("Search :\t") + QString("Press I"));
        monsterSearchText->setPos(540, 200);
        scene->addItem(monsterSearchText);
    }
}

/*
 * Implementation notes: showLoad(), showSave, showLoadOnMainMenu()
 * ----------------------------------------------------------------
 * Show frame of load, save or load on main menu. The difference between
 * <code>showLoad()</code> and <code>showLoadOnMainMenu()</code> is
 * <code>backButton</code>.
 */

void Game::showLoad()
{
    SaveLoad *loadFrame = new SaveLoad();
    loadFrame->showLoadRecord();
}

void Game::showSave()
{
    SaveLoad *saveFrame = new SaveLoad();
    saveFrame->showSaveRecord();
}

void Game::showLoadOnMainMenu()
{
    SaveLoad *loadFrame = new SaveLoad();
    loadFrame->showLoadRecordOnMainMenu();
}

/*
 * Implementation notes: gameOver(), displayGameoverWindow()
 * ---------------------------------------------------------
 * Gameover and show information. Choose to start again or quit.
 */

void Game::gameOver()
{
    // Display gameover window
    QString msg = "YOU WON! \nThis game is our childhood, \n if you like it, give me an A.";
    displayGameoverWindow(msg);
}

void Game::displayGameoverWindow(QString textToDisplay)
{
    // disable all items
    for (int i = 0, n = scene->items().size(); i < n; i++) scene->items()[i]->setEnabled(false);

    // draw the background and text
    drawPanel(0, 0, 640, 440, Qt::darkCyan, 0.65);
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString(textToDisplay));
    QFont titleFont("comic sans", 20);
    titleText->setFont(titleFont);
    titleText->setPos(60, 100);
    scene->addItem(titleText);

    // Play again Button
    Button* playAgain = new Button(QString("Play Again"), 200, 40);
    playAgain->setPos(110, 300);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL(clicked()), this, SLOT(restartGame()));

    // Quit Button
    Button* quitButton = new Button(QString("Quit"), 200, 40);
    quitButton->setPos(410, 300);
    scene->addItem(quitButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

/*
 * Implementation notes: renderFloor(int floor)
 * -------------------------------
 * Re-show map.
 */

void Game::renderFloor(int floor)
{
    maps->show(floor);  // refresh floor
}

/*
 * Implementation note: updateInfo()
 * ------------------------------------------------
 * Update information on the window.
 */

void Game::updateInfo()
{
    // update text
    hpText->setPlainText(QString("HP :\t") + QString::number(hero->getHp()));
    atkText->setPlainText(QString("Attack :\t") + QString::number(hero->getAtk()));
    defText->setPlainText(QString("Defence :\t") + QString::number(hero->getDef()));
    lvText->setPlainText(QString("Lv :\t") + QString::number(hero->getLv()));
    expText->setPlainText(QString("Exp :\t") + QString::number(hero->getExperience()));
    moneyText->setPlainText(QString("Money :\t") + QString::number(hero->getMoney()));
    floorText->setPlainText(QString("Floor :\t") + QString::number(hero->getFloor()));
    yellowKeyText->setPlainText(QString("Yellow key :\t") + QString::number(hero->getYellowKey()));
    blueKeyText->setPlainText(QString("Blue key :\t") + QString::number(hero->getBlueKey()));
    redKeyText->setPlainText(QString("Red key :\t") + QString::number(hero->getRedKey()));

    // update special tool status
    if (hero->getFlyFloor() == true) {
        floorFlyText = new QGraphicsTextItem(QString("Fly :\t") + QString("Press F"));
        floorFlyText->setPos(540, 160);
        scene->addItem(floorFlyText);
    }

    if (hero->getMonsterInfo() == true) {
        monsterSearchText = new QGraphicsTextItem(QString("Search :\t") + QString("Press I"));
        monsterSearchText->setPos(540, 200);
        scene->addItem(monsterSearchText);
    }
}
