#ifndef NPCFLYGAME_H
#define NPCFLYGAME_H

#include <QObject>
#include "Button.h"
#include "Hero.h"
#include "Game.h"
#include "player.h"
#include "score.h"
#include "enemy.h"
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>


class NPCFlyGame: public QObject
{   Q_OBJECT
public:
    // constructor
    NPCFlyGame();

    Player* player;
    Score* score;
    Enemy* enemy;
    QGraphicsScene* scene;


public slots:
    void back();
    void start();

private:
    // private variables

    Button* startButton,* backButton;
    QGraphicsRectItem* miniGameFrame;
    QGraphicsTextItem* miniGameText;
};

#endif // NPCFLYGAME_H
