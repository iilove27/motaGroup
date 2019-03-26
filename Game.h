#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "hero.h"
#include <QMediaPlayer>
#include "monster.h"
#include "map.h"


extern int map2D[11][11];
extern int unwalkableArray[3];
extern int npcIdArray[1];

class Game: public QGraphicsView
{ Q_OBJECT
public:
    Game(QWidget * parent=NULL);
    QGraphicsScene * scene;
    Hero * hero;
    Monster * mons;
    map * maps;
    void mapCompile(int map1d[]);
    void gameOver();
    void displayGameoverWindow(QString textToDisplay);
    void displayMainMenu();
    int getNumOfRedKey();
    void incrementNumOfRedKey();
    int getNumOfBlueKey();
    void incrementNumOfBlueKey();
    int getNumOfYellowKey();
    void incrementNumOfYellowKey();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    void messageBoard(int x, int y, int width, int height, QString text);
public slots:
    void start();
    void restartGame();

private:
    void drawGUI();
    int numOfRedKey_ = 0;
    int numOfYellowKey_ = 0;
    int numOfBlueKey_ = 0;


};

#endif // GAME_H
