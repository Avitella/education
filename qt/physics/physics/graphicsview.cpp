#include "graphicsview.h"
#include "molecule.h"
#include "brownianparticle.h"

#include <iostream>
#include <cmath>

#include <QKeyEvent>
#include <QGraphicsScene>

void GraphicsView::init()
{
    QGraphicsScene *scene = this->scene();
    if (!scene) {
        scene = new QGraphicsScene(this);
        setScene(scene);
    }

    scene->clear();

    if (brownianParticle) {
        delete brownianParticle;
    }
    for (Molecule *molecule : molecules) {
        delete molecule;
    }
    molecules.clear();

    brownianParticle = new BrownianParticle(this);
    scene->addItem(brownianParticle);

    QRect viewRect = parentWidget()->geometry();
    QRect rect(-viewRect.width() / 2, -viewRect.height() / 2, viewRect.width(), viewRect.height());
    scene->setSceneRect(rect);

    for (int i = 0; i < moleculesCount; ++i) {
        Molecule *molecule = new Molecule(this);

        QPoint position;
        position.setX(rect.left() + qrand() % rect.width());
        position.setY(rect.top() + qrand() % rect.height());
        molecule->setPos(position);

        QVector2D vector;
        vector.setX((qrand() * 1.0 - RAND_MAX / 2.0) / RAND_MAX);
        vector.setY((qrand() * 1.0 - RAND_MAX / 2.0) / RAND_MAX);
        molecule->setVector(vector);

        molecules.push_back(molecule);
        scene->addItem(molecule);
    }

    startTimer(1000 / 50);
}

qreal GraphicsView::radius() const
{
    return moleculesRadius;
}

qreal GraphicsView::temperature() const
{
    return sqrt(moleculesTemperature);
}

QPointF GraphicsView::prepare(const QPointF &p)
{
    QRectF const &rect = sceneRect();
    return QPointF(p.x() - 315, p.y() - 300); // TODO: fix it
}

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    moleculesCount(64),
    moleculesRadius(6),
    moleculesTemperature(50.0),
    moleculesWeight(1),
    brownianWeight(4),
    brownianParticle(NULL),
    drowing(false)
{
    init();
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_P:
            moleculesRadius += 1;
            break;
        case Qt::Key_M:
            moleculesRadius -= 1;
            moleculesRadius = std::max(1, moleculesRadius);
            break;
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !drowing) {
        drowing = true;
        drowingPoints.push_back(prepare(event->pos()));
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drowing) {
        drowingPoints.push_back(prepare(event->pos()));
    }
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drowing) {
        drowing = false;
        drowingPoints.push_back(prepare(event->pos()));
        if (drowingPoints.size() >= 3) {
            brownianParticle->init(drowingPoints);
        }
        drowingPoints.clear();
    }
}



void GraphicsView::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    brownianParticle->update(molecules);

    for (size_t i = 0; i < molecules.size(); ++i) {
        for (size_t j = i + 1; j < molecules.size(); ++j) {
            molecules[i]->knock(*molecules[j]);
        }
    }

    for (Molecule *molecule : molecules) {
        molecule->move();
    }
}
