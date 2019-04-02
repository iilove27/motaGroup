
#include "enemybullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemy.h"
#include "Game.h"
#include <qmath.h>
#include <QDebug>
#include "npcflygame.h"
#include "Msgboard.h"

extern Game* game;

enemyBullet::enemyBullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
    setPixmap(QPixmap(":/images/zidan1.png"));

    // make/connect a timer to move() the bullet
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(150);
}

void enemyBullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){
            // increase the score
            //game->score->decrease();
            // TO DO: give specific amount of money based on the score

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete colliding_items[i];
            delete this;
            QString frametext = "I feel so sorry, but you lose the game";
            QString buttontext = "End the Game";
            game->showMiniGameEnd(frametext,buttontext);


            // return (all code below refers to a non existint bullet)
            return;
        }
    }

    int STEP_SIZE = 20;
    double theta = rotation(); // degrees
    //setRotation(40);

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    // if the bullet is off the screen, destroy it
    if (pos().y() < 0 | pos().x()<0 |pos().x()>800 | pos().y()>600){
        scene()->removeItem(this);
        delete this;
    }
}






