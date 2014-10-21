#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "equidistantinterpolation.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_readyForMakeTable_clicked();

private:
    Ui::Widget *ui;
    equidistantInterpolation* interpolation;
    QLabel* stepLabel;
};

#endif // WIDGET_H
