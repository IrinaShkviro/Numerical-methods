#include "myfunction.h"

myFunction::myFunction()
{
}

double myFunction::f(double x)
{
    return qSqrt(x);
}

double myFunction::fFluxion(double x)
{
    return 0.5 / qSqrt(x);
}

double myFunction::fDoubleFluxion(double x)
{
    return - 0.25 / qPow(x, 1.5);
}

double myFunction::myAbs(double x)
{
    if (x < 0) {
        return -x;
    }
    return x;
}
