#ifndef RECORDBUTTON_H
#define RECORDBUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

class RecordButton: public QObject, public QGraphicsRectItem
{   Q_OBJECT
public:
    // constructor
    RecordButton(QString name, int sizeX, int sizeY, QGraphicsItem* parent=nullptr);

    // public methods
    void mousePressEvent(QGraphicsSceneMouseEvent* event);  // click
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);  // hover
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);  // leave
    void setButtonText(QString textContent);
    QString getButtonText();
    std::vector<int> getButtonPos();
    void chosen();
    int getButtonID();
    QGraphicsPixmapItem *yulan;

signals:
    void clicked();

private:
    // private variables
    QGraphicsTextItem* text;
    QString textContent;
    int buttonID;
};
#endif // RECORDBUTTON_H
