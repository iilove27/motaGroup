#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class enemyBullet: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    enemyBullet(QGraphicsItem * parent=0);
    double theta;
public slots:
    void move();
    //void move2();

};

#endif // ENEMYBULLET_H
