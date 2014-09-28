#include "pair.h"

Pair::Pair(qreal start, qreal end):
    startPoint (start)
  , endPoint (end)
{
}

qreal Pair::start()
{
    return startPoint;
}

qreal Pair::end()
{
    return endPoint;
}
