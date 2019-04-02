#include "gamenpc.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "enemy.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include "Game.h"

extern Game* game;
gameNPC::gameNPC(QWidget *parent){

    game->startMiniGame();
}
