#include "npcflygame.h"
#include <QBrush>
#include <QGraphicsView>
#include <QGraphicsScene>


#include <iostream>
#include <fstream>
#include <QBrush>
#include <QImage>
#include <stdlib.h>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QTimer>
#include <errno.h>

#include "saveload.h"

using namespace std;

extern Game * game;

NPCFlyGame::NPCFlyGame()
{
    // create frame
    miniGameFrame = new QGraphicsRectItem();
    miniGameFrame->setRect(100, 0, 440, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    miniGameFrame->setBrush(brush);
    game->scene->addItem(miniGameFrame);
    miniGameFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    miniGameFrame->setFocus();

    // draw the text
    miniGameText = new QGraphicsTextItem(QString("Do you want to play the mini game--Flying Dragon?"));
    QFont titleFont("comic sans", 10);
    miniGameText->setFont(titleFont);
    double txPos = game->width()/2 - miniGameText->boundingRect().width()/2;
    double tyPos = 100;
    miniGameText->setPos(txPos, tyPos);
    game->scene->addItem(miniGameText);

    // Add startButton
    startButton = new Button(QString("Start Game"), 200, 40);
    double hxPos = game->width()/2 - miniGameText->boundingRect().width()/2+50;
    double hyPos = 150;
    startButton->setPos(hxPos, hyPos);
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    game->scene->addItem(startButton);
    buttonMap.insert(std::pair<Button*, int> (startButton, 0));

    // Add BACK button
    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = game->width()/2 - miniGameText->boundingRect().width()/2+50;
    double byPos = 250;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);
    buttonMap.insert(std::pair<Button*, int> (backButton, 1));

    choiceRect = new ChoiceRect(200, 40, 2, false, nullptr, 0, 100);
    choiceRect->setPos(hxPos, hyPos);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();

}

void NPCFlyGame::back()
{
    game->scene->removeItem(choiceRect);
    delete choiceRect;
    game->scene->removeItem(miniGameFrame);
    game->scene->removeItem(miniGameText);
    game->scene->removeItem(startButton);
    game->scene->removeItem(backButton);
    // delete this
    game->hero->setFocusToSelf();
}

void NPCFlyGame::start()
{
    // save the information
    fstream  saveFile;
    saveFile.open("InfoBeforeMiniGame.dat", ios::out|ios::trunc);
    game->maps->saveMapintoRecord("MapBeforeMiniGame.dat"); // save map matrix into file

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

    // start mini game
    game->startMiniGame();
}

void NPCFlyGame::buttonChosen()
{
    cout << "Enter buttonChosen function" << endl;
    int currentChoice = choiceRect->chosen;
    cout << currentChoice;
    std::map<Button*, int>::iterator it;
    for (it = buttonMap.begin(); it != buttonMap.end(); it++) {
        if (it->second == currentChoice) {
            it->first->chosen();
        }
    }
}

