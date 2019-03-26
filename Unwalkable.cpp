#include "unwalkable.h"

unwalkable::unwalkable(QGraphicsItem *parent): QGraphicsPixmapItem (parent) {

}

void unwalkable::show(int unwalkableID)
{
        QString unwalkable_img_path;
        QImage unwalkable_img;
        switch (unwalkableID)
        {
            case 1: unwalkable_img_path = ":/images/wall.png"; break;
            case 2: unwalkable_img_path = ":/images/lava.png"; break;
            case 3: unwalkable_img_path = ":/images/star.png"; break;
        }
        unwalkable_img.load(unwalkable_img_path);
        QPixmap unwalkable_pic=QPixmap::fromImage(unwalkable_img.scaled(40, 40));
        setPixmap(unwalkable_pic);
}
