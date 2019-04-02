
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"
#include "enemybullet.h"
#include <qmath.h>
#include <QDebug>
#include <QTime>
#include <QPoint>
#include "npcflygame.h"
//#include "enemybullet2.h"

extern Game* game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //set random x position
    double random_numberx = generateRandomInteger(0,400);
    double random_numbery = generateRandomInteger(0,200);
    //QPointF position(random_numberx,random_numbery);
    //position = mapToScene(position);

    qDebug()<<random_numberx<<random_numbery<<endl;

    setPos(random_numberx,random_numbery);

    // drew the rect
    setPixmap(QPixmap(":/images/bianfu.png"));
    //setTransformOriginPoint(50,50);
    //setRotation(180);

    // make/connect a timer to shoot() the enemyBullet

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(shoot()));

    QTimer * timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(move()));



    // start the timer
    timer->start(1600);
    timer2->start(1000);


}

double Enemy::generateRandomInteger(int min, int max)
{
    Q_ASSERT(min < max);

        static bool seedStatus;
        if (!seedStatus)
        {
            qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
            seedStatus = true;
        }
        double nRandom = qrand() % (max - min);
        nRandom = min + nRandom;

        return nRandom;

}

void Enemy::move(){
    // move enemy down
    setPos(x(),y()+15);

    // destroy enemy when it goes out of the screen
    if (pos().y() > 440){
        scene()->removeItem(this);
        delete this;
        qDebug()<<"delet the enemy"<<endl;
    }
}

void Enemy::shoot()
{
    // int ORIGINAL_SIZE = 35;

    // +ORIGINAL_SIZE * qCos(qDegreesToRadians(bullet->theta))
    // +ORIGINAL_SIZE * qSin(qDegreesToRadians(bullet->theta))

    enemyBullet* bullet = new enemyBullet;
    bullet->setScale(0.3);
    bullet->setRotation(20);
    bullet->setPos(x()+20,y()+20);
    scene()->addItem(bullet);

    enemyBullet* bullet2 = new enemyBullet;
    bullet2->setScale(0.3);
    bullet2->setRotation(40);
    bullet2->setPos(x()+20,y()+20);
    scene()->addItem(bullet2);

    enemyBullet* bullet3 = new enemyBullet;
    bullet3->setScale(0.3);
    bullet3->setRotation(60);
    bullet3->setPos(x()+20,y()+20);
    scene()->addItem(bullet3);

    enemyBullet* bullet4 = new enemyBullet;
    bullet4->setScale(0.3);
    bullet4->setRotation(80);
    bullet4->setPos(x()+20,y()+20);
    scene()->addItem(bullet4);

    enemyBullet* bullet5 = new enemyBullet;
    bullet5->setScale(0.3);
    bullet5->setRotation(100);
    bullet5->setPos(x()+20,y()+20);
    scene()->addItem(bullet5);

    enemyBullet* bullet6 = new enemyBullet;
    bullet6->setScale(0.3);
    bullet6->setRotation(120);
    bullet6->setPos(x()+20,y()+20);
    scene()->addItem(bullet6);

    enemyBullet* bullet7 = new enemyBullet;
    bullet7->setScale(0.3);
    bullet7->setRotation(140);
    bullet7->setPos(x()+20,y()+20);
    scene()->addItem(bullet7);

    enemyBullet* bullet8 = new enemyBullet;
    bullet8->setScale(0.3);
    bullet8->setRotation(160);
    bullet8->setPos(x()+20,y()+20);
    scene()->addItem(bullet8);

    enemyBullet* bullet9 = new enemyBullet;
    bullet9->setScale(0.3);
    bullet9->setRotation(180);
    bullet9->setPos(x()+20,y()+20);
    scene()->addItem(bullet9);

    enemyBullet* bullet10 = new enemyBullet;
    bullet10->setScale(0.3);
    bullet10->setRotation(200);
    bullet10->setPos(x()+20,y()+20);
    scene()->addItem(bullet10);

    enemyBullet* bullet11 = new enemyBullet;
    bullet11->setScale(0.3);
    bullet11->setRotation(220);
    bullet11->setPos(x()+20,y()+20);
    scene()->addItem(bullet11);

    enemyBullet* bullet12 = new enemyBullet;
    bullet12->setScale(0.3);
    bullet12->setRotation(240);
    bullet12->setPos(x()+20,y()+20);
    scene()->addItem(bullet12);

    enemyBullet* bullet13 = new enemyBullet;
    bullet13->setScale(0.3);
    bullet13->setRotation(260);
    bullet13->setPos(x()+20,y()+20);
    scene()->addItem(bullet13);

    enemyBullet* bullet14 = new enemyBullet;
    bullet14->setScale(0.3);
    bullet14->setRotation(280);
    bullet14->setPos(x()+20,y()+20);
    scene()->addItem(bullet14);

    enemyBullet* bullet15 = new enemyBullet;
    bullet15->setScale(0.3);
    bullet15->setRotation(300);
    bullet15->setPos(x()+20,y()+20);
    scene()->addItem(bullet15);

    enemyBullet* bullet16 = new enemyBullet;
    bullet16->setScale(0.3);
    bullet16->setRotation(320);
    bullet16->setPos(x()+20,y()+20);
    scene()->addItem(bullet16);

    enemyBullet* bullet17 = new enemyBullet;
    bullet17->setScale(0.3);
    bullet17->setRotation(340);
    bullet17->setPos(x()+20,y()+20);
    scene()->addItem(bullet17);


}

/*
void Enemy::shoot2()
{
    enemyBullet2* bullet18 = new enemyBullet2;
    bullet18->setScale(0.2);
    bullet18->setPos(x(),y()+15);
    scene()->addItem(bullet18);

    enemyBullet2* bullet19 = new enemyBullet2;
    bullet19->setScale(0.2);
    bullet19->setPos(x()+20,y()+15);
    scene()->addItem(bullet19);

    enemyBullet2* bullet20 = new enemyBullet2;
    bullet20->setScale(0.2);
    bullet20->setPos(x()+40,y()+15);
    scene()->addItem(bullet20);
}
*/
