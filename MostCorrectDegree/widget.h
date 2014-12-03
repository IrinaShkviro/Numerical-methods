#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "integrator.h"

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
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    Integrator* myIntegrator;
};

#endif // WIDGET_H
