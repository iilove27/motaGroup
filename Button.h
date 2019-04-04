/*
 * File: Button.h
 * --------------
 * This file exports a class <code>Button</code>.
 * Instance:
 *      <code>Play</code>
 *      <code>Load</code>
 *      <code>Quit</code>
 *      <code>Record X</code>
 *      <code>Back</code>
 *      <code>Play Again</code>
 *      TO DO: <code>English</code>
 *      TO DO: <code>中文</code>
 *      TO DO: <code>BGM</code>
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

class Button: public QObject, public QGraphicsRectItem
{   Q_OBJECT
public:
    // constructor
    Button(QString name, int sizeX, int sizeY, QGraphicsItem* parent=nullptr);

    // public methods
    void mousePressEvent(QGraphicsSceneMouseEvent* event);  // click
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);  // hover
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);  // leave
    void setButtonText(QString textContent);
    QString getButtonText();
    std::vector<int> getButtonPos();
    void chosen();
    int getButtonID();

    void disabledColor();
signals:
    void clicked();

private:
    // private variables
    QGraphicsTextItem* text;
    QString textContent;
    int buttonID;
};

#endif // BUTTON_H
