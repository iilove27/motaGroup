/*
 * File: unwalkable.cpp
 * --------------------
 * This file implements unwalkable.h interface.
 */

#include "Unwalkable.h"
#include <QTimer>
using namespace std;

unwalkable::unwalkable(int unwalkableID, QGraphicsItem* parent): QGraphicsPixmapItem (parent)
{
    id = unwalkableID;
}

/*
 * Implementation notes: show
 * --------------------------------
 * Draw the image based on <code>id</code>.
 */

void unwalkable::show()
{
        QString unwalkable_img_path;
        QImage unwalkable_img;

        count = 1;
        QTimer * timer = new QTimer(this);
        timer->start(600);

        // get image path
        switch (id)
        {
            // TO DO: case work
            case 1:
            unwalkable_img_path = ":/images/wall.png";
            break;
            case 2:
            unwalkable_img_path = ":/images/lava1.png";
            image1 = ":/images/lava1.png";
            image2 = ":/images/lava2.png";
            connect(timer,SIGNAL(timeout()),this,SLOT(changePicture()));
            break;
            case 3:
            unwalkable_img_path = ":/images/star1.png";
            image1 = ":/images/star1.png";
            image2 = ":/images/star2.png";
            connect(timer,SIGNAL(timeout()),this,SLOT(changePicture()));
            break;
        }

        // draw the unwalkable area
        unwalkable_img.load(unwalkable_img_path);
        QPixmap unwalkable_pic = QPixmap::fromImage(unwalkable_img.scaled(40, 40)); // 40x40
        setPixmap(unwalkable_pic);
}

/*
 * Implementation notes: getId
 * ---------------------------
 * Return ID number.
 */

int unwalkable::getId()
{
    return id;
}

/*
 * Implementation notes: changePicture()
 * -------------------------------------
 * Change picture of special areas ceaselessly.
 */

void unwalkable:: changePicture()
{
    QString picName;
    QImage unwalkable_img;
    count = count + 1;
    if(count > 2) count = 1;
    switch(count)
    {
    case 1: picName=image1; break;
    case 2: picName=image2; break;
    default: break;
    }
    unwalkable_img.load(picName);
    setPixmap(QPixmap::fromImage(unwalkable_img.scaled(40, 40)));
}
