#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#include <QObject>
#include "myfunction.h"
#include "equidistantinterpolation.h"

class EquationSolver: public equidistantInterpolation
{
    Q_OBJECT
public:
    explicit EquationSolver(equidistantInterpolation* parent);
    double bijectionMethod(double startOfInterval, double endOfInterval, double value);

private:
    myFunction* calculator;
    equidistantInterpolation* parent;

    const double h = 0.001;
    const double err = 0.000000001;
};

#endif // EQUATIONSOLVER_H
