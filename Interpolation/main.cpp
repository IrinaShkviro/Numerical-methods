#include <QtCore>
#include <QCoreApplication>
#include "stdio.h"
#include "iostream"
#include "counter.h"
#include "pair.h"
#include "result.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Counter myCounter;
    Pair initialSegment = myCounter.returnInitialSegment();
    printf("Topic: \"Numerical methods of resolution of the nonlinear algebraical and transcendental equations\"\n");
    qDebug() << "Initial data: Segment from" << initialSegment.start() << "to" << initialSegment.end()<<
                "; our function is " << myCounter.returnFunctionView()<< "; err is " << myCounter.returnErr();
    QList<QList<Result> > results = myCounter.seeResult();
    QList<Pair> segments = myCounter.seeSegments();
    int countOfRoots = segments.count();
    for (int j = 0; j < 5; j++) {
        printf("\n");
        switch (j) {
        case 0:
            printf("Bijection method\n");
            break;
        case 1:
            printf("Newton method\n");
            break;
        case 2:
            printf("Modified Newton method\n");
            break;
        case 3:
            printf("Chord method");
            break;
        case 4:
            printf("Simple iteration method\n");
            break;
        default:
            break;
        }
        QList<Result> curRes = results.takeFirst();
        for (int i = 0; i < countOfRoots; i++) {
            Pair curSegment = segments.at(i);
            qDebug() << "Start segment is" << curSegment.start() << curSegment.end();
            qDebug() << "Count of steps:" << curRes[i].countOfSteps;
            qDebug() << "Approximate solution:" << curRes[i].root;
            qDebug() << "Value of discrepancy:" << curRes[i].errInFunction;
        }
    }
    return a.exec();
}
