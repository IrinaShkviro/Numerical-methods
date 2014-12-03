#include "calculator.h"

Calculator::Calculator(double A, double B, int countOfIntervals) :
    A(A)
  , B(B)
  , countOfIntervals(countOfIntervals)
  , myBase(new BaseCalc())
{
    step = (B - A) / countOfIntervals;
}

double Calculator::f(double x)
{
    return 4*qPow(x, 3) + 2 * x;
}

double Calculator::antiderivative(double x)
{
    return  qPow(x, 4) + qPow(x, 2);
}

double Calculator::correctAntiderivativeValue()
{
    return antiderivative(B) - antiderivative(A);
}

double Calculator::integrateLeftRect(double a, double b)
{
    return (b - a) * f(a);
}

double Calculator::integrateRightRect(double a, double b)
{
    return (b - a) * f(b);
}

double Calculator::integrateMediumRect(double a, double b)
{
    return (b - a) * f((a + b) / 2);
}

double Calculator::integrateTrapeze(double a, double b)
{
    QVector<double> forInsert;
    forInsert << f(a) << f(b);
    return (b - a)/2 * myBase->calculateSum(forInsert);
}

double Calculator::integrateSympson(double a, double b)
{
    QVector<double> forInsert;
    forInsert << f(a) << 4*f((a+b)/2) << f(b);
    return (b-a)/6 * myBase->calculateSum(forInsert);
}

double Calculator::integrateThreeEights(double a, double b)
{
    QVector<double> forInsert;
    forInsert << f(a) << 3*f(a + (b-a)/3) << 3*f(b - (b-a)/3) << f(b);
    return (b-a)/8 * myBase->calculateSum(forInsert);
}

double Calculator::integrateMultipleMediumRect()
{
    QVector<double> forSum;
    double z = A;
    for (int i = 0; i < countOfIntervals; i++) {
        forSum.append(integrateMediumRect(z, z + step));
        z += step;
    }
    return myBase->calculateSum(forSum);
}

double Calculator::integrateMultipleTrapeze()
{
    QVector<double> forSum;
    double z = A;
    for (int i = 0; i < countOfIntervals; i++) {
        forSum.append(integrateTrapeze(z, z+step));
        z += step;
    }
    return myBase->calculateSum(forSum);
}

double Calculator::integrateMultipleSympson()
{
    QVector<double> forSum;
    double z = A;
    for (int i = 0; i < countOfIntervals; i++) {
        forSum.append(integrateSympson(z, z+step));
        z += step;
    }
    return myBase->calculateSum(forSum);
}

BaseCalc* Calculator::useBase()
{
    return myBase;
}
