#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"
#include <QSize>
#include "Game.h"

extern Game* game;
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set bullet sound
    bulletsound = new QMediaPlayer();

    //bulletsound->setMedia(QUrl("qrc:/sounds/bullet.wav"));

    // set graphic
    setPixmap(QPixmap(":/images/SB01.png"));
    // draw score text
    scoreText = new QGraphicsTextItem(QString("Score: ") + QString::number(score));
    scoreText->setPos(20, 20);
    scoreText->setFont(QFont("times",16));
    scoreText->setDefaultTextColor(Qt::white);
    game->scene->addItem(scoreText);
}

void Player::increaseScore()
{
    // remove the original score
    game->scene->removeItem(scoreText);
    // increase the number of socre
    score++;
    // add new score text
    scoreText = new QGraphicsTextItem(QString("Score: ") + QString::number(score));
    scoreText->setPos(20, 20);
    scoreText->setFont(QFont("times",16));
    scoreText->setDefaultTextColor(Qt::white);
    game->scene->addItem(scoreText);
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-15,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+15,y());}
    else if (event->key() == Qt::Key_Up){
        if (pos().x() + 100 < 800)
        setPos(x(),y()-15);}
    else if (event->key() == Qt::Key_Escape){
        QString frametxt = "if you end the game now, you can't have any money";
        QString buttontxt = "End the Game";
        game->showMiniGameEnd(frametxt,buttontxt);

    }

    else if (event->key() == Qt::Key_Down){
        if (pos().x() + 100 < 800)
        setPos(x(),y()+15);
    }
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setScale(0.3);
        bullet->setPos(x(),y());
        scene()->addItem(bullet);

        // play bulletsound
        /*
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
        */

    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    //enemy->setPos(enemy->x()+200,enemy->y()+200);
    scene()->addItem(enemy);

    //feilong1* enemy2= new feilong1();
    //scene()->addItem(enemy2);
}
