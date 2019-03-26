#include "game.h"
#include "monster.h"
#include <stdio.h>
#include <iostream>
#include "unwalkable.h"
#include <QBrush>
#include <QImage>
#include <stdlib.h>
#include "Button.h"
#include <QGraphicsTextItem>
#include "hero.h"
#include <QTimer>

int map2D[11][11];
int unwalkableArray[3] = {1, 2, 3};
int npcIdArray[1] = {44}; // test npc 对话
Game::Game(QWidget *parent)
{
    // set the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,440+100*2,440);
    setBackgroundBrush(QBrush(QImage(":/images/bg.png").scaled(440+100*2, 440)));
    setScene(scene);
    setFixedSize(640,440);

    // 我准备让他自己set focus，但是会出问题...
//    QTimer * timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(setFocusToHero()));
    //    timer->start(4000);
}



void Game::gameOver()
{
    // Display gameover window, can be expanded later
    QString msg;
    msg = "YOU WON! \nThis game is our childhood, \n if you like it, give me an A.";
    displayGameoverWindow(msg);

}

void Game::displayGameoverWindow(QString textToDisplay)
{
    // disable all items
    for (size_t i = 0, n = scene->items().size(); i < n; i++)
    {
        scene->items()[i]->setEnabled(false);
    }
    drawPanel(0, 0, 640, 440, Qt::darkCyan, 0.65);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString(textToDisplay));
    QFont titleFont("comic sans", 20);
    titleText->setFont(titleFont);
    titleText->setPos(60, 100);
    scene->addItem(titleText);

    //Play again
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(110, 300);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL(clicked()), this, SLOT(restartGame()));

    // quit
    Button* quitButton = new Button(QString("Quit"));
    quitButton->setPos(410, 300);
    scene->addItem(quitButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));


}

void Game::displayMainMenu()
{
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Magic Tower"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - titleText->boundingRect().width()/2+50;
    int byPos = 275;
    playButton->setPos(bxPos, byPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - titleText->boundingRect().width()/2+50;
    int qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}


void Game::messageBoard(int x, int y, int width, int height, QString text)
{
    QGraphicsRectItem* board = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    board->setBrush(brush);
    scene->addItem(board);
}


void Game::start()
{
    scene->clear();
    maps = new map();
    maps->getMap2D(0);  // 0-th floor
    maps->show(); // render
    drawGUI();

    // Adding BGM
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgm.mp3"));
    music->play();

    show();
}

void Game::restartGame()
{
    // also need to clear data, not done yet
    scene->clear();
    start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::drawGUI()
{
    drawPanel(0, 0, 100, 440, Qt::darkCyan, 1);
    drawPanel(540, 0, 100, 440, Qt::darkCyan, 1);

    QGraphicsTextItem* HeroInfo = new QGraphicsTextItem(QString("Hero"));
    HeroInfo->setPos(25, 0);
    scene->addItem(HeroInfo);

    QGraphicsTextItem* OtherInfo = new QGraphicsTextItem(QString("Item"));
    OtherInfo->setPos(540, 0);
    scene->addItem(OtherInfo);

    QGraphicsTextItem* yKey = new QGraphicsTextItem(QString("Yellow key :\t") + QString::number(getNumOfYellowKey()));
    QGraphicsTextItem* bKey = new QGraphicsTextItem(QString("Blue key :\t") + QString::number(getNumOfBlueKey()));
    QGraphicsTextItem* rKey = new QGraphicsTextItem(QString("Red key :\t") + QString::number(getNumOfRedKey()));

    yKey->setPos(540, 40);
    bKey->setPos(540, 80);
    rKey->setPos(540, 120);
    scene->addItem(bKey);
    scene->addItem(yKey);
    scene->addItem(rKey);

}


int Game::getNumOfRedKey()
{
    return numOfRedKey_;
}
int Game::getNumOfBlueKey()
{
    return numOfBlueKey_;
}
int Game::getNumOfYellowKey()
{
    return numOfYellowKey_;
}
void Game::incrementNumOfRedKey()
{
    numOfRedKey_++;
}
void Game::incrementNumOfBlueKey()
{
    numOfBlueKey_++;
}
void Game::incrementNumOfYellowKey()
{
    numOfYellowKey_++;
}

