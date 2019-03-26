/*
 * File: Button.cpp
 * --------------------
 * This file implements Button.h interface.
 */

#include "Button.h"

Button::Button(QString name, int sizeX, int sizeY, QGraphicsItem* parent): QGraphicsRectItem (parent)
{
    // draw the button frame
    setRect(0, 0, sizeX, sizeY); // position(0,0) & size(200,40)
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // draw the text
    textContent = name;
    text = new QGraphicsTextItem(textContent, this);
    double xPos = rect().width()/2 - text->boundingRect().width()/2;
    double yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    // set hover event
    setAcceptHoverEvents(true);
}

/*
 * Implementation notes: mousePressEvent()
 * -------------------------------
 * Send <code>clicked()</code> signal and connect.
 * Use to start, load, close, restart, skip, back, set BGM.
 */

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);    // change color & style
    emit clicked();
}

/*
 * Implementation notes: hoverEnterEvent, hoverLeaveEvent
 * ------------------------------------------------
 * Change color whether mouse hover over the button or not.
 */

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);    // change color & style
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);    // change color & style
}

/*
 * Implementation notes: setButtonText(QString textContent)
 * --------------------------------------------------------
 * Change text content on the <code>Button</code>.
 */

void Button::setButtonText(QString textContent)
{
    text->setPlainText(textContent);
    double xPos = rect().width()/2 - text->boundingRect().width()/2;
    double yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);
}

/*
 * Implementation notes: getButtonText()
 * -------------------------------------
 * Return name on the Button.
 */

QString Button::getButtonText()
{
    return textContent;
}
