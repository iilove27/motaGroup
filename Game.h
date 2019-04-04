/*
 * File: Game.h
 * ------------
 * This file exports the class <code>Game</code>, which is the main part
 * to start game.
 */

#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "Monster.h"
#include "Map.h"
#include "Hero.h"
#include "npc.h"
#include "Item.h"
#include "backpack.h"
#include "Choicerect.h"
#include "player.h"
#include "score.h"
#include "enemy.h"

class Game: public QGraphicsView
{   Q_OBJECT
public:
    // constructor
    Game(QWidget* parent=nullptr);

    // public variables
    QGraphicsScene* scene;
    Hero* hero;
    Map* maps;
    backpack* backpackSys;
    std::map<Button*, int> buttonMap;
    Player* player;
    Score* score;
    Enemy* enemy;
    Button* miniGameEndButton;

    QGraphicsTextItem* hpText;
    QGraphicsTextItem* atkText;
    QGraphicsTextItem* defText;
    QGraphicsTextItem* lvText;
    QGraphicsTextItem* expText;
    QGraphicsTextItem* moneyText;
    QGraphicsTextItem* floorText;

    QGraphicsTextItem* yellowKeyText;
    QGraphicsTextItem* blueKeyText;
    QGraphicsTextItem* redKeyText;
    QGraphicsTextItem* floorFlyText;
    QGraphicsTextItem* monsterSearchText;
    QGraphicsTextItem* miniGameEndText;

    //QGraphicsTextItem* scoreText;

    QGraphicsRectItem* miniGameEndFrame;

    // public methods
    void displayMainMenu();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);  // draw information window
    void renderFloor(int f);    // show floor
    void gameOver();
    void displayGameoverWindow(QString textToDisplay);
    void updateInfo();
public slots:
    void subtitleMove();    // subtitle move
    void start();
    void restartGame();
    void drawGUI();
    void showLoad();
    void showSave();
    void showLoadOnMainMenu();
    void buttonChosen();
    void startMiniGame();
    void endMiniGame();
    void showMiniGameEnd(QString frameText,QString buttonText);
    void screenShot();



private:
    ChoiceRect* choiceRect;



};

#endif // GAME_H
