#ifndef BASECALC_H
#define BASECALC_H

#include <QVector>

class BaseCalc
{
public:
    BaseCalc();
    double myAbs(double x);
    double calculateSum (QVector<double> A);
};

#endif // BASECALC_H
