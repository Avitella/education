#ifndef BROWNIANPARTICLE_H
#define BROWNIANPARTICLE_H

#include <QGraphicsItem>
#include "molecule.h"

class GraphicsView;

class BrownianParticle : public QGraphicsItem
{
public:
    BrownianParticle(GraphicsView *w);
    void init(std::vector<QPointF> const &p);
    void update(std::vector<Molecule*> &molecules);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    GraphicsView *widget;
    qreal alpha, w;
    std::vector<QPointF> points;
};

#endif // BROWNIANPARTICLE_H
