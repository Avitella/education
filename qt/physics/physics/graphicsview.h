#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class Molecule;
class BrownianParticle;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);
    void init();
    qreal radius() const;
    qreal temperature() const;
    QPointF prepare(QPointF const &p);


    qreal moleculesWeight;
    qreal brownianWeight;

signals:

public slots:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    int moleculesCount;
    int moleculesRadius;
    qreal moleculesTemperature;

    std::vector<Molecule*> molecules;
    BrownianParticle *brownianParticle;

    bool drowing;
    std::vector<QPointF> drowingPoints;
};

#endif // GRAPHICSVIEW_H
