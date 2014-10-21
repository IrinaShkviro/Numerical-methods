#include "equationsolver.h"

EquationSolver::EquationSolver(equidistantInterpolation *parent):
    parent(parent)
{
}

double EquationSolver::bijectionMethod(double startOfInterval, double endOfInterval, double value)
{
    if (parent->interpolate(startOfInterval) == value) {
        return startOfInterval;
    }
    if (parent->interpolate(endOfInterval) == value) {
        return endOfInterval;
    }
    double start, end, middle, valueInMiddle, valueInStart;
    if (startOfInterval < endOfInterval) {
        start = startOfInterval;
        end = endOfInterval;
        middle = startOfInterval;
    } else {
        start = endOfInterval;
        end = startOfInterval;
        middle = endOfInterval;
    }

    valueInStart = parent->interpolate(start);
    while ((end - start) / 2 > err) {
        middle = (start + end) / 2;
        valueInMiddle = parent->interpolate(middle);
        if (valueInMiddle == value) {
            break;
        }
        if ((valueInMiddle - value) * (valueInStart - value) > 0) {
            start = middle;
            valueInStart = valueInMiddle;
        } else {
            end = middle;
        }
    }
    return middle;
}
