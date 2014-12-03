#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <QObject>
#include "qmath.h"

class Integrator : public QObject
{
    Q_OBJECT
public:
    explicit Integrator(QObject *parent = 0);
    double calcIntegral();
    QString getInfoAboutMoments();
    QString getInfoAboutIndexForOrth();
    QString getInfoAboutNodes();
    QString getInfoAboutIndexForPoli();
    QString getinfoAboutCheck();

signals:

public slots:

private:
    double f(double x);
    double w(double x);
    double antidevForMoments(int k);
    void calculateMoments();
    void calculateIndexForOrthPolinomial();
    void calculateNodes();
    void check();
    void calculateIndexForMostCorrectForm();
    double a = 0;
    double b = 1;
    int N = 2;
    double moment[4];
    double c1, c2;
    double x1, x2;
    double A1, A2;
    double checkCorr, checkCalc;
};

#endif // INTEGRATOR_H
