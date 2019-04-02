#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Bullet: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0);
    QGraphicsTextItem* scoreText;
    int getScore();
public slots:
    void move();
private:
    //int score = 0;

};

#endif // BULLET_H
