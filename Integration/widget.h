#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGridLayout>
#include "qmath.h"
#include "ui_Widget.h"
#include "calculator.h"

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
    void on_calculateButton_clicked();

private:
    Ui::Widget *ui;
    Calculator* myCalc;
    void createWidget();
    void increaseIntervalCount();
    void moreCorrect();
    QTableWidget* resultTable;
    QWidget* resultWidget;
    QGridLayout* resultGrid;
    int countOfIntervals;
    double correctValue, A, B;
    int l;
    double dval0, dval1, dval2, dvall0, dvall1, dvall2;
};

#endif // WIDGET_H
