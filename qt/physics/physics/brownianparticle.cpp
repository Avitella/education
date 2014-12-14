#include "brownianparticle.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include <QBrush>
#include <QPainter>

static qreal sqr(qreal x)
{
    return x * x;
}

static qreal dist(QPointF const &a, QPointF const &b)
{
    return sqrt(sqr(b.x() - a.x()) + sqr(b.y() - a.y()));
}

static QPointF rotate(QPointF const &p, qreal alpha)
{
    qreal x1 = p.x() * cos(alpha) - p.y() * sin(alpha);
    qreal y1 = p.x() * sin(alpha) + p.y() * cos(alpha);
    return QPointF(x1, y1);
}

static qreal VMult(QPointF const &a, QPointF const &b, QPointF const &c)
{
    return (b.x() - a.x()) * (c.y() - b.y()) - (c.x() - b.x()) * (b.y() - a.y());
}

static bool pointsCmp(QPointF const &a, QPointF const &b)
{
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

BrownianParticle::BrownianParticle(GraphicsView *w) :
    widget(w)
{
}

void BrownianParticle::init(const std::vector<QPointF> &p)
{
    alpha = 0;
    w = 0;
    points = p;
    points.push_back(QPointF(0, 0));
    std::sort(points.begin(), points.end(), pointsCmp);
    std::vector<QPointF> up, down;
    up.push_back(points.front());
    down.push_back(points.front());
    for (size_t i = 1; i < points.size(); ++i) {
        if (VMult(points.front(), points[i], points.back()) <= 0) {
            while (up.size() >= 2 && VMult(up[up.size() - 2], up[up.size() - 1], points[i]) >= 0)
                up.pop_back();
            up.push_back(points[i]);
        }
        if (VMult(points.front(), points[i], points.back()) >= 0) {
            while (down.size() >= 2 && VMult(down[down.size() - 2], down[down.size() - 1], points[i]) <= 0)
                down.pop_back();
            down.push_back(points[i]);
        }
    }
    points.clear();
    for (size_t i = 0; i + 1 < up.size(); ++i) {
        points.push_back(up[i]);
    }
    for (size_t i = down.size() - 1; i > 0; --i) {
        points.push_back(down[i]);
    }
}

static qreal getAlpha(QPointF const &a)
{
    if (a.y() == 0.0 && a.x() >= 0) {
        return 0;
    } else if (a.y() == 0.0 && a.x() < 0) {
        return M_PI;
    } else if (a.y() > 0 && a.x() >= 0) {
        return atan(a.y() / a.x());
    } else if (a.y() > 0 && a.x() < 0) {
        return M_PI - atan(a.y() / fabs(a.x()));
    } else if (a.y() < 0 && a.x() >= 0) {
        return 2 * M_PI - atan(fabs(a.y()) / a.x());
    } else if (a.y() < 0 && a.x() <= 0) {
        return M_PI + atan(fabs(a.y()) / fabs(a.x()));
    }
}

static bool checkIntersect(QPointF const &a, QPointF const &b, QPointF const &p, qreal radius)
{
    static int const ITERS = 20;

    qreal dx = b.x() - a.x(), dy = b.y() - a.y();
    qreal l = 0, r = 1.0, ans = dist(a, p);
    for (int i = 0; i < ITERS; ++i) {
        qreal ml = l + (r - l) / 3;
        qreal mr = r - (r - l) / 3;
        QPointF pl(a.x() + dx * ml, a.y() + dy * ml);
        QPointF pr(a.x() + dx * mr, a.y() + dy * mr);
        qreal dl = dist(pl, p);
        qreal dr = dist(pr, p);
        if (dl < dr) {
            r = mr;
        } else {
            l = ml;
        }
        ans = qMin(ans, qMin(dl, dr));
    }

    return ans <= radius;
}

void BrownianParticle::update(std::vector<Molecule *> &molecules)
{
    qreal radius = widget->radius();
    for (Molecule *m : molecules) {
        QPointF p(m->moved());
        for (size_t i = 0; i < points.size(); ++i) {
            QPointF a(points[i]), b(points[(i + 1) % points.size()]);
            a = rotate(a, alpha);
            b = rotate(b, alpha);
            if (checkIntersect(a, b, p, radius)) {
                QPointF pv1 = m->vector().toPointF();
                b -= a;
                QPointF b1 = rotate(b, M_PI / 2.0);
                qreal x1 = b.x(), y1 = b.y(), x2 = b1.x(), y2 = b1.y(), x0 = pv1.x(), y0 = pv1.y();
                qreal det = x1 * y2 - y1 * x2;
                if (det == 0)
                    continue;
                qreal f1 = (x0 * y2 - x2 * y0) / det;
                qreal f2 = (x1 * y0 - x0 * y1) / det;
                if (f2 * x2 + f2 * y2 == 0)
                    continue;
                if (f2 * x2 + f2 * y2 > 0 && x2 + y2 > 0)
                    continue;
                if (f2 * x2 + f2 * y2 < 0 && x2 + y2 < 0)
                    continue;
                pv1 = QPointF(f1 * x1 - f2 * x2, f1 * y1 - f2 * y2);
                m->setVector(QVector2D(pv1));
            }
        }
    }

    alpha += w;
}

QRectF BrownianParticle::boundingRect() const
{
    return QRectF();
}

void BrownianParticle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPolygon elepolygon;
    for (size_t i = 0; i < points.size(); ++i) {
        QPointF p = rotate(points[i], alpha);
        elepolygon << QPoint(p.x(), p.y());
    }

    QBrush brush(Qt::blue);

    QPainterPath tmpPath;
    tmpPath.addPolygon(elepolygon);
    painter->fillPath(tmpPath, brush);
    painter->drawPolygon(elepolygon);
}
