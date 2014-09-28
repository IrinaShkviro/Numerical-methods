#ifndef RESULT_H
#define RESULT_H

#include <QtCore>

class Result
{
public:
    Result(int countOfSteps, qreal root, qreal errInFunction);
    int countOfSteps;
    qreal root;
    qreal errInFunction;
};

#endif // RESULT_H
