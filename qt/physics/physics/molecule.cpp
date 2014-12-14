#include "molecule.h"
#include "graphicsview.h"

#include <algorithm>
#include <cmath>

#include <QPainter>

static QPointF rotate(QPointF const &p, qreal alpha)
{
    qreal x1 = p.x() * cos(alpha) - p.y() * sin(alpha);
    qreal y1 = p.x() * sin(alpha) + p.y() * cos(alpha);
    return QPointF(x1, y1);
}

Molecule::Molecule(GraphicsView *w)
{
    widget = w;
}

void Molecule::setVector(const QVector2D &v)
{
    vect = v;
}

const QVector2D &Molecule::vector() const
{
    return vect;
}

void Molecule::knock(Molecule &m)
{
    qreal radius = widget->radius();
    qreal temperature = widget->temperature();
    QPointF newPoint(pos().x() + vect.x() * temperature, pos().y() + vect.y() * temperature);
    QPointF newPoint2(m.pos().x() + m.vect.x() * temperature, m.pos().y() + m.vect.y() * temperature);
    QVector2D v(newPoint.x() - newPoint2.x(), newPoint.y() - newPoint2.y());
    if (v.lengthSquared() <= 4 * radius * radius) {
        std::swap(vect, m.vect);
    }
}

void Molecule::move()
{
    QGraphicsScene const *scene = widget->scene();
    QRectF const &s = scene->sceneRect();
    QPointF newPos(pos().x() + vect.x() * widget->temperature(), pos().y() + vect.y() * widget->temperature());
    qreal radius = widget->radius();
    if (newPos.x() > s.right() - radius || newPos.x() < s.left() + radius) {
        newPos.setX(newPos.x() > s.right() - radius ? s.right() - radius : s.left() + radius);
        vect.setX(-vect.x());
    }
    if (newPos.y() < s.top() + radius || newPos.y() > s.bottom() - radius) {
        newPos.setY(newPos.y() < s.top() + radius ? s.top() + radius : s.bottom() - radius);
        vect.setY(-vect.y());
    }
    setPos(newPos);
}

QPointF Molecule::moved() const
{
    QPointF p(pos());
    p.setX(p.x() + vect.x() * widget->temperature());
    p.setY(p.y() + vect.y() * widget->temperature());
    return p;
}

QRectF Molecule::boundingRect() const
{
    qreal adjust = 2;
    qreal radius = widget->radius();
    return QRectF( -radius - adjust, -radius - adjust, 2 * radius + adjust, 2 * radius + adjust);
}

void Molecule::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(QColor(Qt::green));
    painter->setPen(QPen(Qt::black, 0));
    qreal radius = widget->radius();
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);
}
