#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <qmath.h>

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
    void on_calculate_clicked();

    void on_maxDegree_textChanged();

    void on_valuesFrom_textChanged();

    void on_valuesTo_textChanged();

    void on_degree_textChanged();

    void on_interpolationPoint_textChanged();

    void on_radioButton_checked();

private:
    Ui::Widget *ui;
    double f(double x);
    double startData[101][103];
    QLineEdit* degreeLineEdit;
    QLineEdit* pointLineEdit;
    int countOfPoints;
    double interpolationPoint;
    double polinomDegree;
    void qsortStartData(int left, int right);
    double lagrangeMethod(double x);
    double w(double x, int k);
    double newtonMethod(double x);
    QRadioButton* newtonMethodButton;
    QRadioButton* lagrangeMethodButton;
    QWidget* degreeWindow;
    QGridLayout* degreeLayout;
    QLabel* resultLabel;
    QLabel* errorDegreeLabel;
    QLabel* errorInterpolationPointLabel;
    QLabel* errorMethodIsNotChoosenLabel;
    double myAbs(double x);
};

#endif // WIDGET_H
