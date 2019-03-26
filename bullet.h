#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

class Bullet: public QGraphicsRectItem{

public:
    Bullet();
public slots:
    void move();
};

#endif // BULLET_H
