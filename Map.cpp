#include "map.h"
#include "game.h"
#include "hero.h"

extern Game * game;

map::map()
{

}

void map::getMap2D(int floor)
{
    if (floor == 0)  // 之后换成自动读取文件的方式
    {
        for (int i = 0; i < 3; i++) unwalkableArray[i] = i+1;

        // map for the first floor
        int map[121] = {
            1, 3, 3, 3, 3, 94, 3, 3, 3, 3, 1,
            1, 3, 3, 3, 3, 91, 3, 3, 3, 3, 1,
            1, 3, 3 ,3 ,3 ,0 ,3 ,3 ,3, 3, 1,
            1, 3, 3, 3, 3 ,/*17*/0, 3, 3, 3, 3, 1,
            1, 3, 3, 3, 3 ,/*16*/0, 3, 3, 3 ,3 ,1,
            1 ,3, 3, 3, 3, /*15*/0, 3, 3, 3, 3, 1,
            1 ,1 ,3 ,3 ,3, 0 ,3, 3, 3, 1, 1,
            1 ,1 ,1, 1, 1, /*96*/0 ,1 ,1 ,1, 1, 1,
            2 ,1 ,2 ,1 ,44 ,0 ,0 ,1 ,2 ,1 ,2,
            2 ,2 ,2 ,2 ,2, 0, 2 ,2 ,2 ,2 ,2,
            2 ,2 ,2 ,2 ,2 ,96 ,2 ,2 ,2 ,2 ,2
        };

        for (int i = 0; i < 11; i++)  // i should be row num, j should be col num 从地图坐标上来看； 但是从Qt的坐标来看是反的
            for (int j = 0; j < 11; j++)
                map2D[i][j] = map[i*11+j];

    }
}

int map::getHeroPosX()  // Hero initial Position at each floor, now it's only the 0-th floor
{
    return 200;
}
int map::getHeroPosY()
{
    return 400;
}

void map::show()
{
    // create everything
    hero = new Hero();
    hero -> setPos(300, 400);
    hero->show();
    Monster* mons[121];
    unwalkable* wall[121];  // just in case 小array装不下，动态数组又太麻烦
    int countMons = 0;
    int countWall = 0;
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
        {
            switch (map2D[i][j])
            {
            case 1: wall[countWall] = new unwalkable();
                wall[countWall]->setPos(j*40 + 100, i*40);
                wall[countWall]->show(1);
                countWall++;
                break;
            case 2: wall[countWall] = new unwalkable();
                wall[countWall]->setPos(j*40 + 100, i*40);
                wall[countWall]->show(2);
                countWall++;
                break;
            case 3: wall[countWall] = new unwalkable();
                wall[countWall]->setPos(j*40 + 100, i*40);
                wall[countWall]->show(3);
                countWall++;
                break;
            case 44: mons[countMons] = new Monster();
                mons[countMons]->setPos(j * 40 + 100, i * 40);
                mons[countMons]->show(0); // 0 should be Monster's id, here 0 is just a sample
                countMons++; // count how many monsters are there
                break;
            }

        }

    // put everything on the scene
    game->scene ->addItem(hero);
    for (int i = 0, n = countMons; i < n; i++)
        game->scene ->addItem(mons[i]);
    for (int i = 0, n = countWall; i < n; i++)
        game->scene ->addItem(wall[i]);
    hero ->setFlag(QGraphicsItem::ItemIsFocusable);
    hero ->setFocus();

}
