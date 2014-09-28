#ifndef PAIR_H
#define PAIR_H

#include <QtCore/qmath.h>

class Pair
{
public:
    Pair(qreal start, qreal end);

    qreal start();
    qreal end();

private:
    qreal startPoint;
    qreal endPoint;
};

#endif // PAIR_H
