#include <QApplication>
#include <QGraphicsScene>
#include <Hero.h>
#include <QGraphicsView>
#include <Monster.h>
#include <QDebug>
#include <QMediaPlayer>
#include <Game.h>


Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
