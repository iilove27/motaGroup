#ifndef GAMENPC_H
#define GAMENPC_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"

class gameNPC: public QGraphicsView{
public:
    gameNPC(QWidget * parent=0);

};

#endif // GAMENPC_H
