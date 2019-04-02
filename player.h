#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QSize>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int score = 0;
    Player(QGraphicsItem * parent=0);
    void increaseScore();
    void keyPressEvent(QKeyEvent * event);
    QSize *picSize;
    QGraphicsTextItem* scoreText;
public slots:
    void spawn();
private:
    QMediaPlayer * bulletsound;
};

#endif // PLAYER_H
