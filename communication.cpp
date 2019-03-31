/*
 * File: communication.cpp
 * ----------------
 * This file implements communication.h interface.
 */

#include "communication.h"
#include "Game.h"
#include "Button.h"
#include <iostream>

extern Game* game;

communication::communication(NPC* npc, QGraphicsItem* parent): QGraphicsRectItem(parent)
{
    // set text based on ID
    id = npc->getId();
    switch(id) {
    case 101:
        communicationText.enqueue(QString("史莱姆👼: 来啦老弟"));
        communicationText.enqueue(QString("恶龙🐲: ？"));
        communicationText.enqueue(QString("史莱姆👼: 你老婆就在里面"));
        communicationText.enqueue(QString("恶龙🐲: ？？？"));
        communicationText.enqueue(QString("史莱姆👼: 你愿意去救他🐎"));
        break;
    }

    // create communication frame
    setRect(100, 50, 440, 220);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
    game->scene->addItem(this);
    setFlag(QGraphicsItem::ItemIsFocusable);    // avoid KeyPressEvents
    setFocus();

    // draw the text
    text = new QGraphicsTextItem(communicationText.dequeue());
    text->setPos(200,100);
    game->scene->addItem(text);
}

/*
 * Implementation notes: keyPressEvent(QKeyEvent* event)
 * -----------------------------------------------------
 * Use Key_Space to continue conversation. Judge whether there is option choice.
 */

void communication::keyPressEvent(QKeyEvent* event)
{
    // Key_Space to continue conversation
    if (event->key() == Qt::Key_Space)
    {
        if (!communicationText.isEmpty()) {
            QString currentSentence = communicationText.dequeue();  // show next content
            text->setPlainText(currentSentence);

            // check whether there is option choice
            if (checkOption(currentSentence)) {
                buttonMap = showButton101();
                showChoiceInit(buttonOption1->getButtonPos()[0], buttonOption1->getButtonPos()[1]);
            }
        }
        else if (communicationText.isEmpty()) {
            // if there is no other words then remove and focus back
            game->scene->removeItem(this);
            game->scene->removeItem(text);
            delete this;

            game->hero->setFocusToSelf();
        }
    }
}

/*
 * Implementation notes: checkOption(QString sentence)
 * ---------------------------------------------------
 * Judge whether there is option based on <code>sentence</code>.
 */

bool communication::checkOption(QString sentence)
{
    if (sentence == QString("史莱姆👼: 你愿意去救他🐎")){
        return true;
    }
    return false;
}

void communication::showChoiceInit(int x, int y)
{
    choiceRect = new ChoiceRect(80, 40, 3, true, nullptr, 160);
    choiceRect->setPos(x, y);
    connect(choiceRect, SIGNAL(spacePressed()), this, SLOT(buttonChosen()));
    game->scene->addItem(choiceRect);
    choiceRect->setFlag(QGraphicsItem::ItemIsFocusable);
    choiceRect->setFocus();
}

/*
 * Implementation notes: showButtonX()
 * -------------------------------------
 * Different NPC X would have different Option. Show button.
 */

std::map<Button*, int> communication::showButton101()
{
    std::map<Button*, int> buttonMap;
    // draw button
    buttonOption1 = new Button("我愿意", 80, 40);
    buttonOption1->setPos(120, 220);     // 每个选项之间的间隔，安排一下
    connect(buttonOption1, SIGNAL(clicked()), this, SLOT(addText10101()));
    buttonMap.insert(std::pair<Button*, int> (buttonOption1, 0));
    game->scene->addItem(buttonOption1);

    buttonOption2 = new Button("我不愿意", 80, 40);
    buttonOption2->setPos(280, 220);
    connect(buttonOption2, SIGNAL(clicked()), this, SLOT(addText10102()));
    buttonMap.insert(std::pair<Button*, int> (buttonOption2, 1));
    game->scene->addItem(buttonOption2);

    buttonOption3 = new Button("我就是路过", 80, 40);
    buttonOption3->setPos(440, 220);
    connect(buttonOption3, SIGNAL(clicked()), this, SLOT(addText10103()));
    buttonMap.insert(std::pair<Button*, int> (buttonOption3, 2));
    game->scene->addItem(buttonOption3);

    return buttonMap;
}

/*
 * Implementation notes: addTextXY()
 * -------------------------------------
 * Different NPC X would have different contents Y after choice, add
 * relevant contents to <code>communicationText</code>.
 */

void communication::addText10101()
{
    // add communication content
    communicationText.enqueue(QString("恶龙🐲: 虽然不知道我老婆是谁 但我愿意！"));
    communicationText.enqueue(QString("史莱姆👼: 那给你一个红钥匙哈 加油鸭"));

    // remove button, show content & set focus back
    game->scene->removeItem(buttonOption1);
    game->scene->removeItem(buttonOption2);
    game->scene->removeItem(buttonOption3);
    game->scene->removeItem(choiceRect);

    text->setPlainText(communicationText.dequeue());
    setFocus();
}

void communication::addText10102()
{
    // add communication content
    communicationText.enqueue(QString("恶龙🐲: 我没有 我不是 别瞎说啊"));
    communicationText.enqueue(QString("史莱姆对恶龙一顿暴打之后..."));
    communicationText.enqueue(QString("恶龙🐲: 呜呜呜我愿意"));
    communicationText.enqueue(QString("史莱姆👼: 那给你一个红钥匙哈 加油鸭"));

    // remove button, show content & set focus back
    game->scene->removeItem(buttonOption1);
    game->scene->removeItem(buttonOption2);
    game->scene->removeItem(buttonOption3);
    game->scene->removeItem(choiceRect);

    text->setPlainText(communicationText.dequeue());
    setFocus();
}

void communication::addText10103()
{
    // add communication content
    cout << "Enter addText10103 function" << endl;

    communicationText.enqueue(QString("我莫得老婆，你说你🐴呢?"));

    game->scene->removeItem(buttonOption1);
    game->scene->removeItem(buttonOption2);
    game->scene->removeItem(buttonOption3);
    game->scene->removeItem(choiceRect);

    text->setPlainText(communicationText.dequeue());
    setFocus();
}

void communication::buttonChosen()
{
    int currentChoice = choiceRect->getCurrentChoice();
    std::map<Button*, int>::iterator it;
    for (it = buttonMap.begin(); it != buttonMap.end(); it++) {
        if (it->second == currentChoice) {
            it->first->chosen();
        }
    }
}
