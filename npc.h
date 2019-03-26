/*
 * File: npc.h
 * ------------
 * This file exports the class <code>NPC</code>, which is use to store
 * relevant information about a NPC.
 */

#ifndef NPC_H
#define NPC_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class NPC: public QGraphicsPixmapItem
{
public:
    // constructor
    NPC(int npcID, QGraphicsItem* parent=nullptr);

    // public methods
    int getId();
    void show();
    int getEmotion();                       // emotion
    void setEmotion(int newEmotion);
    int checkEmotionValid(int newEmotion);  // emotion between -100 and 100
    bool checkVisit();                      // check whether NPC is able to be visited
    void setVisit(bool newVisit=true);
    bool getRequirementPosition(int requirementIndex);
    void setRequirementPosition(int requirementIndex, bool newPosition=true);

private:
    // private variables
    int id;
    QString name;
    bool visit; // check whether npc is able to be visited
    int emotion;
    bool npcRequirement[10];
};

#endif // NPC_H
