#include "basecalc.h"

BaseCalc::BaseCalc()
{
}

double BaseCalc::myAbs(double x)
{
    if (x < 0) {
        return -x;
    }
    return x;
}

double BaseCalc::calculateSum(QVector<double> A)
{
    int size = A.size();
    double res = 0;
    for (int j = 0; j < size; j++) {
        res += A.at(j);
    }
    return res;
}
