#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QVector>
#include "qmath.h"
#include "basecalc.h"

class Calculator : public QObject
{
    Q_OBJECT
public:
     Calculator(double A, double B, int countOfIntervals);
    double correctAntiderivativeValue();
    double integrateLeftRect(double a, double b);
    double integrateRightRect(double a, double b);
    double integrateMediumRect(double a, double b);
    double integrateTrapeze(double a, double b);
    double integrateSympson(double a, double b);
    double integrateThreeEights(double a, double b);
    double integrateMultipleMediumRect();
    double integrateMultipleTrapeze();
    double integrateMultipleSympson();
    BaseCalc* useBase();

signals:

public slots:

private:
    BaseCalc* myBase;
    double f (double x);
    double antiderivative(double x);
    int countOfIntervals;
    double step;
    double A, B;
};

#endif // CALCULATOR_H
