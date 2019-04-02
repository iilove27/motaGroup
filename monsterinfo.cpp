#include "monsterinfo.h"
#include "Monster.h"

monsterInfo::monsterInfo()
{
    findMonster();
    for (int monsNum = 0; monsNum < monsterID.size(); monsNum++) {
        Monster* monster = new Monster(monsterID[monsNum]);
        hpInfo.enqueue(new QGraphicsTextItem(QString("hp:")+QString::number(monster->getHp())));
        atkInfo.enqueue(new QGraphicsTextItem(QString("atk:")+QString::number(monster->getAtk())));
        defInfo.enqueue(new QGraphicsTextItem(QString("def:")+QString::number(monster->getDef())));
        expInfo.enqueue(new QGraphicsTextItem(QString("exp:")+QString::number(monster->getExperience())));
        moneyInfo.enqueue(new QGraphicsTextItem(QString("money:")+QString::number(monster->getMoney())));
        imagePath.enqueue(QString(":/images/")+QString::number(monsterID[monsNum])+QString(".png"));
        monsterImage.enqueue(new QGraphicsPixmapItem());
    }
}

void monsterInfo::showFrame()
{
    // create frame
    monsterFrame = new QGraphicsRectItem();
    monsterFrame->setRect(100, 0, 440, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    monsterFrame->setBrush(brush);
    game->scene->addItem(monsterFrame);
    monsterFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    monsterFrame->setFocus();

    // back Button
    backButton = new Button(QString("BACK"), 120, 30);
    backButton->setPos(400, 400);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);

    // Add Image & info
    QFont textFont("comic sans", 10);

    for (int monsNum = 0; monsNum < monsterID.size(); monsNum++) {
        if (monsNum % 2 == 0) {
            QImage monster_img;
            monster_img.load(imagePath[monsNum]);
            QPixmap hero_pic = QPixmap::fromImage(monster_img.scaled(80, 80));
            monsterImage[monsNum]->setPixmap(QPixmap::fromImage(monster_img.scaled(60, 60)));
            monsterImage[monsNum]->setPos(120, 80+80*monsNum/2);
            game->scene->addItem(monsterImage[monsNum]);

            hpInfo[monsNum]->setPos(210,80+80*monsNum/2);
            hpInfo[monsNum]->setFont(textFont);
            game->scene->addItem(hpInfo[monsNum]);

            atkInfo[monsNum]->setPos(210,90+80*monsNum/2);
            atkInfo[monsNum]->setFont(textFont);
            game->scene->addItem(atkInfo[monsNum]);

            defInfo[monsNum]->setPos(210,100+80*monsNum/2);
            defInfo[monsNum]->setFont(textFont);
            game->scene->addItem(defInfo[monsNum]);

            expInfo[monsNum]->setPos(210,110+80*monsNum/2);
            expInfo[monsNum]->setFont(textFont);
            game->scene->addItem(expInfo[monsNum]);

            moneyInfo[monsNum]->setPos(210,120+80*monsNum/2);
            moneyInfo[monsNum]->setFont(textFont);
            game->scene->addItem(moneyInfo[monsNum]);
        }
        else {

            QImage monster_img;
            monster_img.load(imagePath[monsNum]);
            QPixmap hero_pic = QPixmap::fromImage(monster_img.scaled(80, 80));
            monsterImage[monsNum]->setPixmap(QPixmap::fromImage(monster_img.scaled(60, 60)));
            monsterImage[monsNum]->setPos(340, 80+80*monsNum/2);
            game->scene->addItem(monsterImage[monsNum]);

            hpInfo[monsNum]->setPos(430,80+80*monsNum/2);
            hpInfo[monsNum]->setFont(textFont);
            game->scene->addItem(hpInfo[monsNum]);

            atkInfo[monsNum]->setPos(430,90+80*monsNum/2);
            atkInfo[monsNum]->setFont(textFont);
            game->scene->addItem(atkInfo[monsNum]);

            defInfo[monsNum]->setPos(430,100+80*monsNum/2);
            defInfo[monsNum]->setFont(textFont);
            game->scene->addItem(defInfo[monsNum]);

            expInfo[monsNum]->setPos(430,110+80*monsNum/2);
            expInfo[monsNum]->setFont(textFont);
            game->scene->addItem(expInfo[monsNum]);

            moneyInfo[monsNum]->setPos(430,120+80*monsNum/2);
            moneyInfo[monsNum]->setFont(textFont);
            game->scene->addItem(moneyInfo[monsNum]);
        }
    }
}

bool monsterInfo::checkRepeated(int id)
{
    for (int i = 0; i < monsterID.size(); i++) {
        if (id == monsterID[i]) return false;
    }
    return true;
}


void monsterInfo::back()
{
    game->scene->removeItem(monsterFrame);
    game->scene->removeItem(backButton);
    for (int monsNum = 0; monsNum < monsterID.size(); monsNum++) {
        game->scene->removeItem(monsterImage[monsNum]);
        game->scene->removeItem(hpInfo[monsNum]);
        game->scene->removeItem(atkInfo[monsNum]);
        game->scene->removeItem(defInfo[monsNum]);
        game->scene->removeItem(expInfo[monsNum]);
        game->scene->removeItem(moneyInfo[monsNum]);
    }


    game->hero->setFocusToSelf();
}

void monsterInfo::findMonster()
{
    int floor = game->hero->getFloor();
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            int id = game->maps->map2D[floor][i][j];
            if (checkRepeated(id)) {
                switch(id) {
                case 201: case 202: case 203: monsterID.enqueue(id); break;
                default: continue;
                }
            }
        }
    }
}



