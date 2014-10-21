#ifndef EQUIDISTANTINTERPOLATION_H
#define EQUIDISTANTINTERPOLATION_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "myfunction.h"

class equidistantInterpolation : public QWidget
{
    Q_OBJECT
public:
    explicit equidistantInterpolation(QWidget *parent = 0);
    double generateTable(double a, double b, int countOfpoints);
    double interpolate(double interpolationPoint);

signals:

public slots:

private slots:
    void on_calculate_clicked();
    void on_repeatButton_clicked();
    void on_newTaskButton_clicked();
    void on_degreeLineEdit_textChanged();
    void on_interpolationPointLineEdit_textChanged();
    void on_calculateInvertedButton_clicked();
    void on_invertedInterpolationPointLineEdit_textChanged();
    void on_repeatInvertButton_clicked();
    void on_fluxionButton_clicked();

private:
    QWidget* mainWindow;
    QGridLayout* mainGrid;
    double fullInterpolate(double interpolationPoint);


    void getData();
    double calculateInvertedTable(double invertedPoint);
    void qsortStartData(int left, int right);

    double startOfInterval, endOfInterval, step;
    double startOfInvertedInterval, endOfInvertedInterval;
    int countOfPoints, polinomDegree;
    double startData[101][103];
    double invertedStartData[101][103];
    myFunction* calculator;

    QLabel* errorDegreeLabel;
    QLabel* errorInterpolationPointLabel;
    QLabel* interpolationPointLabel;
    QLineEdit* degreeLineEdit;
    QLineEdit* interpolationPointLineEdit;
    QPushButton* calculatePushButton;

    QLabel* valueInPointLabel;
    QLabel* errorInResultLabel;
    QLabel* repeatLabel;
    QPushButton* repeatButton;
    QPushButton* newTaskButton;

    QLineEdit* invertedInterpolationPointLineEdit;
    QLabel* errorInInvertedIntervalLabel;
    QLabel* resultOfInvertedTableLabel;
    QLabel* errorOfInvertedTableLabel;
    QLabel* resultOfInvertedEquationLabel;
    QLabel* errorOfInvertedEquationLabel;
    QPushButton* calculateInvertedButton;

    QLabel* repeatInvertLabel;
    QPushButton* repeatInvertButton;
    QPushButton* fluxionButton;
    QTableWidget *startValues;

    QString defineCase;
};

#endif // EQUIDISTANTINTERPOLATION_H
