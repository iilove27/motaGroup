#ifndef UNWALKABLE_H
#define UNWALKABLE_H

#include <QGraphicsItem>

class unwalkable: public QGraphicsPixmapItem
{
public:
    unwalkable(QGraphicsItem * parent=0);
    void init(int id);
    void show(int);

private:
    int id;
};

#endif // UNWALKABLE_H
