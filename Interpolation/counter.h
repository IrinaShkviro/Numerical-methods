#ifndef COUNTER_H
#define COUNTER_H
#include <QList>
#include <QtCore/qmath.h>
#include "pair.h"
#include "result.h"

class Counter
{
public:
    Counter();
    QList<QList<Result> > seeResult();
    QList<Pair> seeSegments();
    Pair returnInitialSegment();
    QString returnFunctionView();
    qreal returnErr();

private:
    QList<Pair> segments;
    QList<Result> results0;
    QList<Result> results1;
    QList<Result> results2;
    QList<Result> results3;
    QList<Result> results4;
    int currentSegment;

    void defineRoots(int definer);
    void separateRoots();
    qreal f (qreal x);
    qreal fFluxion (qreal x);
    qreal notNullFluxion(qreal a, qreal b);
    qreal chooseStartPoint(qreal a, qreal b);
    qreal g (qreal x);
    void bijectionMethod(qreal a, qreal b);
    void newtonMethod(qreal a, qreal b);
    void modifiedNewtonMethod(qreal a, qreal b);
    void chordMethod(qreal a, qreal b);
    void simpleIterationMethod(qreal a, qreal b);

    const qreal A = -1;
    const qreal B = 5;
    const qreal err = 0.00001;
    const qreal h = 0.1;
    const int countOfMethods = 5;
};

#endif // COUNTER_H
