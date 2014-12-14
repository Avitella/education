#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <vector>

#include <QWidget>

class BrownianParticle;
class Molecule;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    void initGraphicsView();

    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
