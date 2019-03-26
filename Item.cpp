/*
 * File: Item.cpp
 * ----------------
 * This file implements Item.h interface.
 */

#include <QTimer>
#include <QDebug>
#include "Item.h"

Item::Item(int itemID, QGraphicsItem *parent): QGraphicsPixmapItem (parent)
{
    // set id
    id = itemID;
}

/*
 * Implementation notes: openDoor()
 * --------------------------------
 * Open the door and delete the door.
 */

void Item::openDoor()
{
    QTimer::singleShot(100, this, SLOT(changePictureFirst()));
}

/*
 * Implementation notes: show()
 * --------------------------
 * Draw the picture of items.
 */

void Item::show()
{
    QString item_img_path;
    QImage item_img;

    // find image path
    switch (id){
        case 301: item_img_path = ":/images/301.png"; break;
        case 303: item_img_path = ":/images/303.png"; break;
        case 304: item_img_path = ":/images/304.png"; break;
        case 4: item_img_path = ":/images/4_1.png"; break;
        case 5: item_img_path = ":/images/5_1.png"; break;
        case 6: item_img_path = ":/images/6.png"; break;
        case 7: item_img_path = ":/images/7.png"; break;
    }

    // load and draw image
    item_img.load(item_img_path);
    QPixmap item_pic = QPixmap::fromImage(item_img.scaled(40, 40));
    setPixmap(item_pic);
}

/*
 * Implementation notes: getId()
 * -----------------------------
 * return id number.
 */

int Item::getId()
{
    return id;
}

/*
 * Implementation nots: changePictureX();
 * --------------------------------------
 * Change picture for four times.
 */

void Item::changePictureFirst()
{
    QString item_img_path_2;
    QImage item_img_2;

    item_img_path_2 = QString(":/images/")+QString::number(id)+QString("_2.png");
    item_img_2.load(item_img_path_2);

    QPixmap item_pic_2 = QPixmap::fromImage(item_img_2.scaled(40, 40));
    setPixmap(item_pic_2);
    QTimer::singleShot(100, this, SLOT(changePictureSecond()));
}

void Item::changePictureSecond()
{
    QString item_img_path_3;
    QImage item_img_3;

    item_img_path_3 = QString(":/images/")+QString::number(id)+QString("_3.png");
    item_img_3.load(item_img_path_3);

    QPixmap item_pic_3 = QPixmap::fromImage(item_img_3.scaled(40, 40));
    setPixmap(item_pic_3);
    QTimer::singleShot(100, this, SLOT(changePictureThird()));
}

void Item::changePictureThird()
{
    QString item_img_path_4;
    QImage item_img_4;

    item_img_path_4 = QString(":/images/")+QString::number(id)+QString("_4.png");
    item_img_4.load(item_img_path_4);

    QPixmap item_pic_4 = QPixmap::fromImage(item_img_4.scaled(40, 40));
    setPixmap(item_pic_4);
    QTimer::singleShot(100, this, SLOT(changePictureFourth()));
}

void Item::changePictureFourth()
{
    delete this;
}
