/*
 * File: npc.cpp
 * --------------------
 * This file implements npc.h interface.
 */

#include "npc.h"

NPC::NPC(int npcID, QGraphicsItem *parent): QGraphicsPixmapItem (parent)
{
    id = npcID;     // set id
    visit = true;   // set whether npc could be visited
    emotion = 0;    // set emotion = 0

    // set name based on id
    switch (id)
    {
        case 101: name = "xiannv"; break;
        case 102: name = "business"; break;
    }
}

/*
 * Implementation notes: show()
 * --------------------------
 * Draw the picture of npc.
 */

void NPC::show()
{
    QString npc_img_path;
    QImage npc_img;

    // find image path
    switch (id){
        case 101: npc_img_path = ":/images/101.png"; break;
        case 102: npc_img_path = ":/images/102.png"; break;
    }

    // load and draw image
    npc_img.load(npc_img_path);
    QPixmap npc_pic = QPixmap::fromImage(npc_img.scaled(40, 40));
    setPixmap(npc_pic);
}

/*
 * Implementation notes: getEmotion(), setEmotion(), checkEmotionValid()
 * ---------------------------------------------------------------
 * Get & set value of <code>emotion</code>. Ensure the value is between -100 and 100.
 */

int NPC::getEmotion()
{
    return emotion;
}

void NPC::setEmotion(int newEmotion)
{
    emotion = checkEmotionValid(newEmotion);
}

int NPC::checkEmotionValid(int newEmotion)
{
    if (newEmotion < -100)
    {
        return -100;    // set no smaller than -100
    }
    else if (newEmotion > 100)
    {
        return 100;     // set no larger than 100
    }
    return newEmotion;
}

/*
 * Implementation notes: checkVisit(), setVisit()
 * ---------------------------------------------------------------
 * Get & set value of <code>visit</code>.
 * <code>true</code> means npc is able to be visited.
 * <code>false</code> means npc is unable to be visited.
 */

bool NPC::checkVisit()
{
    return visit;
}

void NPC::setVisit(bool newVisit)
{
    visit = newVisit;
}

/*
 * Implementation notes: getRequirementPosition(int requirementIndex),
 *                       setRequirementPosition(int requirementIndex, bool newPosition)
 * ---------------------------------------------------------------
 * Get & set value of <code>npcRequirement</code>.
 * true means <code>npcRequirement[requirementIndex]</code> is finished.
 * false means <code>npcRequirement[requirementIndex]</code> is  not finished.
 */

bool NPC::getRequirementPosition(int requirementIndex)
{
    return npcRequirement[requirementIndex];
}

void NPC::setRequirementPosition(int requirementIndex, bool newPosition)
{
    npcRequirement[requirementIndex] = newPosition;
}

/*
 * Implementation notes: getId()
 * -----------------------------
 * Return id.
 */

int NPC::getId()
{
    return id;
}
