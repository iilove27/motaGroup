/*
 * File: battle.h
 * --------------
 * This file exports a class <code>battle</code>. Information about monster
 * and hero would be input. After checking whether the hero is stronger than
 * monster, <code>battleFrame</code> shows with Hps of hero and monster
 * decreasing in turn. Delete frame and set focus back to <code>Hero</code>.
 */

#ifndef BATTLE_H
#define BATTLE_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QObject>
#include <QTimer>
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include <time.h>
#include <Msgboard.h>
#include "Choicerect.h"

class battle: public QObject
{   Q_OBJECT
public:
    // constructor
    battle(Monster* monster, Hero* hero);

    // public methods
    void battleFrameShow(Monster * monster, Hero * hero);
    bool checkBattle();
    void updateText();
    void showBattleButton();
    void update();
    void checkCritical();
    void checkDodge();
    std::map<Button*, int> buttonMap;


public slots:
    void battleOnce();  // show
    void Autoroundbattle();
    void stopbattle();
    void skill();
    void backpack();
    void back();
    void UseSkill1();
    void UseSkill2();
    void UseSkill3();
    void CriticalDisapper();
    void DodgeDisapper();
    void StopAuto();
    void HeroBacktoPlace();
    void MonsterBacktoPlace();
    void SkillShow1();
    void SkillShow2();
    void SkillShow3();
    void SkillShow4();
    void buttonChosen();

private:
    // private variables
    int monsterId, monsterHp, monsterAtk, monsterDef,monsterMoney,monsterEXP;
    int heroHp, heroAtk, heroDef;
    int monsterHarm, heroHarm;  // harm = atk - def
    int battleSignal;
    int StatusOfStun,StatusOfBurn,signal;
    double random;

    QString monsterHpInfo, monsterAtkInfo, monsterDefInfo;
    QString heroHpInfo, heroAtkInfo, heroDefInfo;

    QGraphicsTextItem* monsterHpText,* monsterAtkText,* monsterDefText,*monsterStun,*monsterBurn;
    QGraphicsTextItem* heroHpText,* heroAtkText,* heroDefText;
    QGraphicsTextItem* critical, *dodge;
    QGraphicsRectItem* battleFrame, *skillFrame, *backpackFrame;
    QGraphicsPixmapItem* hero_img_battle;
    QGraphicsPixmapItem* monster_img_battle;

    QGraphicsPixmapItem* skill_img1, *skill_img2, *skill_img3;

    Button* battlebutton1,* battlebutton2,* battlebutton3, *battlebutton4,*battlebutton5,*battlebutton6;
    Button* backButton, *skill1,*skill2,*skill3;
    QTimer* timer;
    ChoiceRect* choiceRect;
};

#endif // BATTLE_H
