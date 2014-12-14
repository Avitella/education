#ifndef MOLECULE_H
#define MOLECULE_H

#include <QGraphicsItem>
#include <QVector2D>

#include "mainwidget.h"
#include "graphicsview.h"

class Molecule : public QGraphicsItem
{
public:
    Molecule(GraphicsView *widget);

    void setVector(QVector2D const &v);
    QVector2D const &vector() const;
    void knock(Molecule &m);
    void move();
    QPointF moved() const;

protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    GraphicsView *widget;
    QVector2D vect;
};

#endif // MOLECULE_H
