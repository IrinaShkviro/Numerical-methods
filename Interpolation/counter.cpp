#include "counter.h"

Counter::Counter() :
    currentSegment(0)
{
}

Pair Counter::returnInitialSegment()
{
    return Pair(A, B);
}

QString Counter::returnFunctionView()
{
    return "e^x - x^3 + 2x";
}

qreal Counter::returnErr()
{
    return err;
}

qreal Counter::f(qreal x)
{
    return qCos(x);
}

qreal Counter::fFluxion(qreal x)
{
    return - qSin (x)  ;
}

void Counter::separateRoots()
{
    segments.clear();
    qreal x1 = A, x2 = A + h;
    qreal y1 = f (x1), y2 = f (x2);
    if (y1 * y2 < 0)
    {
        segments.append(Pair(x1, x2));
    }
    while (x2 <= B)
    {
        x1 = x2;
        x2 = x1 + h;
        y1 = y2;
        y2 = f (x2);
        if (y1 * y2 < 0)
        {
            segments.append(Pair(x1, x2));
        }
    }
}

void Counter::bijectionMethod(qreal a, qreal b)
{
    int countOfSteps = 0;
    if (f(a) == 0) {
        results0.append(Result(countOfSteps, a, 0));
        return;
    }
    if (f (b) == 0) {
        results0.append(Result(countOfSteps, b, 0));
        return;
    }
    qreal x1, x2, x3;
    x1 = a, x2 = b, x3 = a;
    while ((x2 - x1) / 2 > err) {
        countOfSteps ++;
        x3 = (x1 + x2) / 2;
        if (f (x3) == 0) {
            break;
        }
        if (f (x3) * f (x1) > 0) {
            x1 = x3;
        } else {
            x2 = x3;
        }
    }

    results0.append(Result(countOfSteps, x3, f (x3)));
}

qreal Counter::notNullFluxion(qreal a, qreal b)
{
    qreal step = (a + b ) / 1000;
    qreal x1 = a + step;
    while (fFluxion(x1) == 0 && x1 <= b)
    {
        x1 += step;
    }
    return x1;
}

qreal Counter::chooseStartPoint(qreal a, qreal b)
{
    if (a > b) {
        qreal z = a;
        a = b;
        b = z;
    }
    qreal x0 = a;
    if (fFluxion(x0) == 0) {
        x0 = notNullFluxion(a, b);
    }
  /*  qreal x1 = x0 - (f (x0)) / (fFluxion (x0));
    while (! ((f(x1) > -f(x0)) && (f(x1) < f(x0)))) {
        x0 = notNullFluxion(x0, x1);
        x1 = x0 - (f (x0)) / (fFluxion (x0));
    }*/
    return x0;
}

void Counter::newtonMethod(qreal a, qreal b)
{
    int countOfSteps = 0;
    if (f(a) == 0) {
        results1.append(Result(countOfSteps, a, 0));
        return;
    }
    if (f (b) == 0) {
        results1.append(Result(countOfSteps, b, 0));
        return;
    }
    qreal x1, x2;
    x1 = chooseStartPoint(a, b);
    if (f (x1) == 0) {
        results1.append(Result(countOfSteps, x1, f (x1)));
        return;
    }
    x2 = x1 - (f (x1)) / (fFluxion (x1));
    while ( ((x2 - x1 > err) or (x2 - x1) < -err)) {
        countOfSteps ++;
        if (f (x2) == 0) {
            break;
        }
        x1 = x2;
        x2 = x1 - (f (x1)) / (fFluxion (x1));
    }
     results1.append(Result(countOfSteps, x2, f (x2)));
}

void Counter::modifiedNewtonMethod(qreal a, qreal b)
{
    int countOfSteps = 0;
    if (f(a) == 0) {
        results2.append(Result(countOfSteps, a, 0));
        return;
    }
    if (f (b) == 0) {
        results2.append(Result(countOfSteps, b, 0));
        return;
    }
    qreal x1, x2, x0;
    x0 = chooseStartPoint(a, b);
    if (f (x0) == 0) {
        results2.append(Result(countOfSteps, x0, f (x0)));
        return;
    }
    x1 = x0 - (f (x0)) / (fFluxion (x0));
    countOfSteps ++;
    if (f (x1) == 0) {
        results2.append(Result(countOfSteps, x1, f (x1)));
        return;
    }
    x2 = x1 - (f (x1)) / (fFluxion (x0));
    while ( (x2 - x1 > err) or ((x2 - x1) < -err)) {
        countOfSteps ++;
        if (f (x2) == 0) {
            break;
        }
        x1 = x2;
        x2 = x1 - (f (x1)) / (fFluxion (x0));
    }
    results2.append(Result(countOfSteps, x2, f (x2)));
}

void Counter::chordMethod(qreal a, qreal b)
{
    int countOfSteps = 0;
    if (f(a) == 0) {
        results3.append(Result(countOfSteps, a, 0));
        return;
    }
    if (f (b) == 0) {
        results3.append(Result(countOfSteps, b, 0));
        return;
    }
    qreal x1, x2, x3;
    x1 = a;
    x2 = b;
    countOfSteps ++;
    while ( (x2 - x1 > err) or ((x2 - x1) < -err) ) {
        countOfSteps ++;
        x3 = x2 - (f (x2) * (x2 - x1)) / (f (x2) - f (x1));
        if (f (x3) == 0) {
            break;
        }
        x1 = x2;
        x2 = x3;
    }
    results3.append(Result(countOfSteps, x3, f (x3)));
}

qreal Counter::g(qreal x)
{
    return x + f(x) * f(x);
}

void Counter::simpleIterationMethod(qreal a, qreal b)
{
    int countOfSteps = 0;
    if (f(a) == 0) {
        results4.append(Result(countOfSteps, a, 0));
        return;
    }
    if (f (b) == 0) {
        results4.append(Result(countOfSteps, b, 0));
        return;
    }
    qreal x1, x2;
    x1 = chooseStartPoint(a, b);
    if (f (x1) == 0) {
        results4.append(Result(countOfSteps, x1, f (x1)));
        return;
    }
    x2 = g (x1);
    while ( (x2 - x1 > err) or ((x2 - x1) < -err) ) {
        countOfSteps ++;
        if (f (x2) == 0) {
            break;
        }
        x1 = x2;
        x2 = g (x1);
    }
    results4.append(Result(countOfSteps, x2, f(x2)));
}

QList<Pair> Counter::seeSegments()
{
    return segments;
}

QList <QList<Result> >  Counter::seeResult()
{
    results0.clear();
    results1.clear();
    results2.clear();
    results3.clear();
    results4.clear();
    separateRoots();
    for (int i = 0; i < countOfMethods; i++) {
        defineRoots(i);
    }
    QList <QList<Result> > result;
    result.append(results0);
    result.append(results1);
    result.append(results2);
    result.append(results3);
    result.append(results4);
    return result;
}

void Counter::defineRoots(int definer)
{
    qreal a, b;
    int countOfRoots = segments.count();
    for (currentSegment = 0; currentSegment < countOfRoots; currentSegment++) {
        Pair curSegment = segments.at(currentSegment);
        a = curSegment.start();
        b = curSegment.end();
        switch (definer) {
        case 0:
            bijectionMethod(a, b);
            break;
        case 1:
            newtonMethod(a, b);
            break;
        case 2:
            modifiedNewtonMethod(a, b);
            break;
        case 3:
            chordMethod(a, b);
            break;
        case 4:
            simpleIterationMethod(a, b);
            break;
        default:
            break;
        }
    }
}
