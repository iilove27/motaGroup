/*
 * File: battle.cpp
 * ----------------
 * This file implements battle.h interface.
 */

#include "battle.h"
#include <iostream>

using namespace std;

extern Game *game;

battle::battle(Monster * monster, Hero * hero)
{
    StatusOfStun=0;
    StatusOfBurn=0;
    signal=0;
    // if (!checkBattle()) delete this;     // bug

    // get Monster hp & atk & def
    monsterId = monster->getId();
    monsterHp = monster->getHp();
    monsterAtk = monster->getAtk();
    monsterDef = monster->getDef();
    monsterMoney=monster->getMoney();
    monsterEXP=monster->getExperience();
    monsterHpInfo = "HP:\t" + QString::number(monsterHp);
    monsterAtkInfo = "ATK:\t" + QString::number(monsterAtk);
    monsterDefInfo = "DEF:\t" + QString::number(monsterDef);
    // get Hero hp & atk & def
    heroHp = hero->getHp();
    heroAtk = hero->getAtk();
    heroDef = hero->getDef();
    heroHpInfo = "HP:\t" + QString::number(heroHp);
    heroAtkInfo = "ATK:\t" + QString::number(heroAtk);
    heroDefInfo = "DEF:\t" + QString::number(heroDef);

    // get harm value (>=0)
    monsterHarm = max(0, monsterAtk-heroDef);
    heroHarm = max(0, heroAtk-monsterDef);

    battleFrameShow(monster,hero); // show battle frame
}

/*
 * Implementation notes: battleFrameShow(Monster* monster, Hero* hero)
 * ---------------------------------------------------------------------
 * This function creates a <code>battleFrame</code> and displays information
 * relevant to battle.
 */

void battle::battleFrameShow(Monster * monster, Hero * hero)
{
    // create battle frame
    battleFrame = new QGraphicsRectItem();
    battleFrame->setRect(100, 50, 440, 330);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    battleFrame->setBrush(brush);
    game->scene->addItem(battleFrame);
    battleFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    battleFrame->setFocus();

    // create battle information & image
    monsterStun=new QGraphicsTextItem("眩晕");
    monsterBurn=new QGraphicsTextItem("灼伤");
    critical = new QGraphicsTextItem("会心一击");
    dodge=new QGraphicsTextItem("闪避");
    monsterHpText = new QGraphicsTextItem(monsterHpInfo);
    monsterAtkText = new QGraphicsTextItem(monsterAtkInfo);
    monsterDefText = new QGraphicsTextItem(monsterDefInfo);
    monsterHpText->setPos(200,50);
    monsterAtkText->setPos(200,100);
    monsterDefText->setPos(200,150);

    heroHpText = new QGraphicsTextItem(heroHpInfo);
    heroAtkText = new QGraphicsTextItem(heroAtkInfo);
    heroDefText = new QGraphicsTextItem(heroDefInfo);
    heroHpText->setPos(330,50);
    heroAtkText->setPos(330,100);
    heroDefText->setPos(330,150);

    game->scene->addItem(monsterHpText);
    game->scene->addItem(monsterAtkText);
    game->scene->addItem(monsterDefText);
    game->scene->addItem(heroHpText);
    game->scene->addItem(heroAtkText);
    game->scene->addItem(heroDefText);

    // add monster & hero image to battle frame
    hero_img_battle = new QGraphicsPixmapItem();
    QString hero_img_path = ":/images/down1.png";
    QImage hero_img;
    hero_img.load(hero_img_path);
    QPixmap hero_pic = QPixmap::fromImage(hero_img.scaled(60, 60));
    hero_img_battle->setPixmap(hero_pic);
    hero_img_battle->setPos(450,80);
    game->scene->addItem(hero_img_battle);

    monster_img_battle = new QGraphicsPixmapItem();
    QString monster_img_path = QString(":/images/") + QString::number(monsterId) + QString(".png");
    QImage monster_img;
    monster_img.load(monster_img_path);
    QPixmap monster_pic = QPixmap::fromImage(monster_img.scaled(60, 60));
    monster_img_battle->setPixmap(monster_pic);
    monster_img_battle->setPos(110,80);
    game->scene->addItem(monster_img_battle);



    skill_img1 = new QGraphicsPixmapItem();
    QString skill_img1_path = ":/images/S1.png";
    QImage skillImg1;
    skillImg1.load(skill_img1_path);
    QPixmap Skill_pic1 = QPixmap::fromImage(skillImg1.scaled(60, 60));
    skill_img1->setPixmap(Skill_pic1);
    skill_img1->setPos(450,160);

    skill_img2 = new QGraphicsPixmapItem();
    QString skill_img2_path = ":/images/S2.png";
    QImage skillImg2;
    skillImg2.load(skill_img2_path);
    QPixmap Skill_pic2 = QPixmap::fromImage(skillImg2.scaled(60, 60));
    skill_img2->setPixmap(Skill_pic2);
    skill_img2->setPos(450,160);


    skill_img3 = new QGraphicsPixmapItem();
    QString skill_img3_path = ":/images/S3.png";
    QImage skillImg3;
    skillImg3.load(skill_img3_path);
    QPixmap Skill_pic3 = QPixmap::fromImage(skillImg3.scaled(60, 60));
    skill_img3->setPixmap(Skill_pic3);
    skill_img3->setPos(450,160);






    // TO DO: add name to battle frame
    showBattleButton();
    // update information


}

/*
 * Implementation notes: checkBattle(Monster* monster, Hero* hero)
 * ---------------------------------------------------------------
 * Check whether hero is stronger than monster. Only hp, atk & def would
 * be considered.
 */

bool battle::checkBattle()
{
    int numOfRounds = monsterHp / heroHarm;
    if (numOfRounds*monsterHarm >= heroHp) return false;
    return true;
}

/*
 * Implemenetation notes: updateText()
 * -----------------------------------
 * Upate HP text after every round of battle.
 */

void battle::updateText()
{
    monsterHpInfo = "HP:\t" + QString::number(monsterHp);
    heroHpInfo = "HP:\t" + QString::number(heroHp);
    monsterHpText->setPlainText(monsterHpInfo);
    heroHpText->setPlainText(heroHpInfo);
}

void battle::Autoroundbattle()
{
    // battle
    signal=1;
    game->scene->removeItem(battlebutton1);
//    game->scene->removeItem(choiceRect);

    cout << "remove choiceRect in autoroundbattle" << endl;
    game->scene->addItem(battlebutton5);
//    buttonMap.erase(buttonMap.find(battlebutton1));
//    buttonMap.insert(std::pair<Button*, int> (battlebutton5, 0));
//    game->scene->addItem(choiceRect);
//    choiceRect->setFocus();

    timer = new QTimer(this);
    timer->start(700);
    connect(timer,SIGNAL(timeout()),this,SLOT(battleOnce()));


    // 中止自动战斗，写不来！

}


void battle::StopAuto()
{
     timer->stop();
     game->scene->removeItem(battlebutton5);
//     game->scene->removeItem(choiceRect);
     game->scene->addItem(battlebutton1);
//     buttonMap.erase(buttonMap.find(battlebutton5));
//     buttonMap.insert(std::pair<Button*, int> (battlebutton1, 0));
//     game->scene->addItem(choiceRect);
//     choiceRect->setFocus();

}



void battle::showBattleButton()
{
    buttonMap.clear();

    battlebutton1 = new Button("自动攻击", 80, 40);
    battlebutton1->setPos(220, 200);
    connect(battlebutton1, SIGNAL(clicked()), this, SLOT(Autoroundbattle()));
    game->scene->addItem(battlebutton1);
    buttonMap.insert(std::pair<Button*, int> (battlebutton1, 0));

    battlebutton2 = new Button("普通攻击", 80, 40);
    battlebutton2->setPos(340, 200);
    connect(battlebutton2, SIGNAL(clicked()), this, SLOT(battleOnce()));
    game->scene->addItem(battlebutton2);
    buttonMap.insert(std::pair<Button*, int> (battlebutton2, 1));


    battlebutton4 = new Button("逃跑", 80, 40);
    battlebutton4->setPos(340, 260);
    connect(battlebutton4, SIGNAL(clicked()), this, SLOT(stopbattle()));
    game->scene->addItem(battlebutton4);
    buttonMap.insert(std::pair<Button*, int> (battlebutton4, 3));


    battlebutton3 = new Button("技能", 80, 40);
    battlebutton3->setPos(220, 260);
    connect(battlebutton3, SIGNAL(clicked()), this, SLOT(skill()));
    game->scene->addItem(battlebutton3);
    buttonMap.insert(std::pair<Button*, int> (battlebutton3, 2));

    battlebutton5 = new Button("中止自动", 80, 40);
    battlebutton5->setPos(220, 200);
    connect(battlebutton5, SIGNAL(clicked()), this, SLOT(StopAuto()));
//    buttonMap.insert(std::pair<Button*, int> (battlebutton1, 0));

//    battlebutton6 = new Button("背包", 80, 40);
//    battlebutton6->setPos(340, 260);
//    connect(battlebutton6, SIGNAL(clicked()), this, SLOT(backpack()));
//    game->scene->addItem(battlebutton6);
//    buttonMap.insert(std::pair<Button*,int> (battlebutton1, 0));

    choiceRect = new ChoiceRect(80, 40, 4, true, nullptr, 120, 60, true);
    choiceRect->setPos(220, 200);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();

}

void battle::update()
{

    game->hero->setHp(heroHp);
    game->hero->setMoney(game->hero->getMoney()+monsterMoney);
    game->hero->setExperience(game->hero->getExperience()+monsterEXP);
    game->updateInfo();

    // update Map
     game->maps->updateMap(game->hero->getFloor(), game->hero->getPosX(), game->hero->getPosY()-1, 0);
    delete game->maps->mons[game->hero->getPosY()*11-11+game->hero->getPosX()];

}



/*
 * Implementation notes: battleOnce()
 * ----------------------------------
 * If <code>monsterHp</code> is no smaller than 0, battle once;
 * otherwise, delete the battle frame. <code>timer</code> should
 * be stopped, or it would continue all the time.
 */



void battle::HeroBacktoPlace()
{
    hero_img_battle->setPos(450,80);
}

void battle::MonsterBacktoPlace()
{
    monster_img_battle->setPos(110,80);
}



void battle::battleOnce()
{

    checkCritical();
    hero_img_battle->setPos(430,80);
    QTimer::singleShot(300, this, SLOT(HeroBacktoPlace()));
    if (StatusOfBurn>0)  monsterHp -= 0.2* heroHarm;
    if (StatusOfBurn==1){
        StatusOfBurn--;
        game->scene->removeItem(monsterBurn);
    }
    else StatusOfBurn--;

    if (monsterHp <= 0)
    {
        stopbattle();
        update();
    }
    updateText();

    if (StatusOfStun==0){
         checkDodge();
         monster_img_battle->setPos(130,80);
         QTimer::singleShot(300, this, SLOT(MonsterBacktoPlace()));
         updateText();
    }
    else {
        StatusOfStun--;
        game->scene->removeItem(monsterStun);
    }
}

void battle::stopbattle()
{
    if (signal==1)  timer->stop();
    signal=0;
    updateText();
    game->scene->removeItem(choiceRect);
    game->scene->removeItem(battleFrame);
    game->scene->removeItem(monsterHpText);
    game->scene->removeItem(monsterAtkText);
    game->scene->removeItem(monsterDefText);
    game->scene->removeItem(heroHpText);
    game->scene->removeItem(heroAtkText);
    game->scene->removeItem(heroDefText);
    game->scene->removeItem(hero_img_battle);
    game->scene->removeItem(monster_img_battle);
    game->scene->removeItem(battlebutton1);
    game->scene->removeItem(battlebutton2);
    game->scene->removeItem(battlebutton3);
    game->scene->removeItem(battlebutton4);
    game->scene->removeItem(battlebutton5);
//    game->scene->removeItem(battlebutton6);
    game->scene->removeItem(monsterStun);
    game->scene->removeItem(monsterBurn);
    StatusOfBurn=0;
    StatusOfStun=0;
    QString updateText;
   if (monsterHp > 0) updateText="你个弟弟竟然跑了";
   else{
   updateText = "你获得了\t" + QString::number(monsterMoney)+"元以及\t"+ QString::number(monsterEXP)+"经验";
   }

    MsgBoard * msg = new MsgBoard(updateText, 100, 100, 440, 150);
    game->scene->addItem(msg);
    game->hero->setFocusToSelf(); // focus back
}

void battle::skill()
{
    skillbuttonMap.clear();

    delete choiceRect;
    skillFrame = new QGraphicsRectItem();
    skillFrame->setRect(220, 0, 200, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    skillFrame->setBrush(brush);
    game->scene->addItem(skillFrame);
    skillFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    skillFrame->setFocus();

    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = 220;
    double byPos = 400;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);
    skillbuttonMap.insert(std::pair<Button*, int> (backButton, 3));

    skill1 = new Button(QString("龙之俯冲(伤害与眩晕）"), 200, 60);
     bxPos = 220;
     byPos = 0;
    skill1->setPos(bxPos, byPos);
    connect(skill1, SIGNAL(clicked()), this, SLOT(UseSkill1()));
    game->scene->addItem(skill1);
    skillbuttonMap.insert(std::pair<Button*, int> (skill1, 0));


    skill2 = new Button(QString("大字爆炎（伤害与灼烧）"), 200, 60);
     bxPos = 220;
     byPos = 60;
     skill2->setPos(bxPos, byPos);
     connect(skill2, SIGNAL(clicked()), this, SLOT(UseSkill2()));
     game->scene->addItem(skill2);
     skillbuttonMap.insert(std::pair<Button*, int> (skill2, 1));


     skill3 = new Button(QString("自我再生（回复血量）"), 200, 60);
     bxPos = 220;
     byPos = 120;
    skill3->setPos(bxPos, byPos);
    connect(skill3, SIGNAL(clicked()), this, SLOT(UseSkill3()));
    game->scene->addItem(skill3);
    skillbuttonMap.insert(std::pair<Button*, int> (skill3, 2));

    choiceRect = new ChoiceRect(200, 60, 4, false, nullptr, 0, 60, false, true);
    choiceRect->setPos(220, 0);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(skillbuttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();

    // 如果没有技能的话(也就是只有一个choice)，就setPos到back上先。

}

void battle::back()
{
    game->scene->removeItem(choiceRect);
    game->scene->removeItem(skillFrame);
//    game->scene->removeItem(backpackFrame);
    game->scene->removeItem(backButton);
    game->scene->removeItem(skill1);
    game->scene->removeItem(skill2);
    game->scene->removeItem(skill3);

    choiceRect = new ChoiceRect(80, 40, 4, false, nullptr, 120, 60, true);
    choiceRect->setPos(220, 200);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();
}
void battle::SkillShow1()
{
    game->scene->addItem(skill_img1);
    QTimer::singleShot(200, this, SLOT(SkillShow2()));
}

void battle::SkillShow2()
{
    game->scene->removeItem(skill_img1);
    game->scene->addItem(skill_img2);
    QTimer::singleShot(200, this, SLOT(SkillShow3()));
}

void battle::SkillShow3()
{
    game->scene->removeItem(skill_img2);
    game->scene->addItem(skill_img3);
    QTimer::singleShot(200, this, SLOT(SkillShow4()));
}


void battle::SkillShow4()
{
    game->scene->removeItem(skill_img3);
}

void battle::UseSkill1()
{

     StatusOfStun=1;
     monsterHp -= 2*heroAtk;
     if (monsterHp > 0)  SkillShow1();
     game->scene->addItem(monsterStun);
     if (monsterHp <= 0)
     {
         game->scene->removeItem(choiceRect);
         stopbattle();
         update();
     }

     updateText();
     game->scene->removeItem(skillFrame);
     game->scene->removeItem(backButton);
     game->scene->removeItem(skill1);
     game->scene->removeItem(skill2);
     game->scene->removeItem(skill3);
     delete choiceRect;

     if (monsterHp > 0) {
         choiceRect = new ChoiceRect(80, 40, 4, false, nullptr, 120, 60, true);
         choiceRect->setPos(220, 200);
         connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
         game->scene->addItem(choiceRect);
         choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
         choiceRect->setFocus();

         monsterStun->setPos(120,170);
     }

}


void battle::UseSkill2()
{
     StatusOfBurn=3;
     monsterHp -= 2.5*heroAtk;
     if (monsterHp > 0)  SkillShow1();
     monster_img_battle->setPos(130,80);
     QTimer::singleShot(300, this, SLOT(MonsterBacktoPlace()));
     game->scene->addItem(monsterBurn);
     if (monsterHp <= 0)
     {
         game->scene->removeItem(choiceRect);
         stopbattle();
         update();
     }
     heroHp -= monsterHarm;
     updateText();
     qDebug() << "6666";
     game->scene->removeItem(choiceRect);
     game->scene->removeItem(skillFrame);
     game->scene->removeItem(backButton);
     game->scene->removeItem(skill1);
     game->scene->removeItem(skill2);
     game->scene->removeItem(skill3);
     monsterBurn->setPos(120,210);

     if (monsterHp > 0) {
         choiceRect = new ChoiceRect(80, 40, 4, false, nullptr, 120, 60, true);
         choiceRect->setPos(220, 200);
         connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
         game->scene->addItem(choiceRect);
         choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
         choiceRect->setFocus();

     }



}


void battle::UseSkill3()
{
     heroHp += 5;
     monster_img_battle->setPos(130,80);
     heroHp -= monsterHarm;
     SkillShow1();
     QTimer::singleShot(300, this, SLOT(MonsterBacktoPlace()));
     updateText();
     game->scene->removeItem(skillFrame);
     game->scene->removeItem(backButton);
     game->scene->removeItem(skill1);
     game->scene->removeItem(skill2);
     game->scene->removeItem(skill3);
     game->scene->removeItem(choiceRect);

     choiceRect = new ChoiceRect(80, 40, 4, false, nullptr, 120, 60, true);
     choiceRect->setPos(220, 200);
     connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
     game->scene->addItem(choiceRect);
     choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
     choiceRect->setFocus();



}


void battle::checkCritical()
{
    random=rand() / double(RAND_MAX);
    if (random<0.7) monsterHp -= heroHarm;
    else {
        monsterHp -= 2*heroHarm;
        critical->setPos(450,240);
        game->scene->addItem(critical);
        QTimer::singleShot(400, this, SLOT(CriticalDisapper()));
    }
}

void battle::checkDodge()
{
    random=rand() / double(RAND_MAX);
    if (random<0.7) heroHp -= monsterHarm;
    else{
        dodge->setPos(460,300);
        game->scene->addItem(dodge);
        QTimer::singleShot(400, this, SLOT(DodgeDisapper()));
    }
}



void battle::CriticalDisapper()
{
  game->scene->removeItem(critical);
}

void battle::DodgeDisapper()
{
    game->scene->removeItem(dodge);
}


void battle::backpack()
{

    backpackFrame = new QGraphicsRectItem();
    backpackFrame->setRect(220, 0, 200, 440);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    backpackFrame->setBrush(brush);
    game->scene->addItem(backpackFrame);
    backpackFrame->setFlag(QGraphicsItem::ItemIsFocusable); // avoid events' influence
    backpackFrame->setFocus();

    backButton = new Button(QString("BACK"), 200, 40);
    double bxPos = 220;
    double byPos = 400;
    backButton->setPos(bxPos, byPos);
    connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
    game->scene->addItem(backButton);


}

void battle::buttonChosen()
{
    std::cout << "Enter buttonChosen function" << std::endl;
    int currentChoice = choiceRect->chosen;
    std::cout << currentChoice;
    std::map<Button*, int>::iterator it;
    for (it = buttonMap.begin(); it != buttonMap.end(); it++) {
        if (it->second == currentChoice) {
            it->first->chosen();
        }
    }
}

void battle::skillbuttonChosen()
{
    std::cout << "Enter skillbuttonChosen function" << std::endl;
    int currentChoice = choiceRect->chosen;
    std::cout << currentChoice;
    std::map<Button*, int>::iterator it;
    for (it = skillbuttonMap.begin(); it != skillbuttonMap.end(); it++) {
        if (it->second == currentChoice) {
            it->first->chosen();
        }
    }
}

