#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <qmath.h>

class myFunction
{
public:
    myFunction();
    double f(double x);
    double fFluxion(double x);
    double fDoubleFluxion(double x);
    double myAbs(double x);
};

#endif // MYFUNCTION_H
