#include "integrator.h"

Integrator::Integrator(QObject *parent) :
    QObject(parent)
{
}

double Integrator::f(double x)
{
    return qSin(x);
}

double Integrator::w(double x)
{
    return qPow(x, 0.25);
}

double Integrator::antidevForMoments(int k)
{
    return qPow(b, (k + 1.25))/(k + 1.25) - qPow(a, (k + 1.25))/(k + 1.25);
}

void Integrator::calculateMoments()
{
    for (int i = 0; i < 4; i++) {
        moment[i] = antidevForMoments(i);
    }
}

void Integrator::calculateIndexForOrthPolinomial()
{
    double delta = moment[1]*moment[1] - moment[0]*moment[2];
    if (delta == 0) {
        return;
    }
    double delta1 = -moment[2]*moment[1] + moment[3]*moment[0];
    double delta2 = -moment[3]*moment[1] + moment[2]*moment[2];
    c1 = delta1/delta;
    c2 = delta2/delta;
}

void Integrator::calculateNodes()
{
    double discr = c1*c1 - 4*c2;
    if (discr < 0) {
        return;
    }
    x1 = (-c1 + qSqrt(discr))/2;
    x2 = (-c1 - qSqrt(discr))/2;
}

void Integrator::calculateIndexForMostCorrectForm()
{
    double delta = x2 - x1;
    if (delta == 0) {
        return;
    }
    double delta1 = moment[0]*x2 - moment[1];
    double delta2 = moment[1] - moment[0]*x1;
    A1 = delta1/delta;
    A2 = delta2/delta;
}

void Integrator::check()
{
    checkCorr = 4*(qPow(b, 4.25) - qPow(a, 4.25))/17;
    checkCalc = A1*qPow(x1, 3) + A2*qPow(x2, 3);
}

double Integrator::calcIntegral()
{
    calculateMoments();
    calculateIndexForOrthPolinomial();
    calculateNodes();
    calculateIndexForMostCorrectForm();
    check();
    return A1*f(x1) + A2*f(x2);
}

QString Integrator::getInfoAboutMoments()
{
    QString res;
    for (int i = 0; i < 4; i++) {
        res += QString::number(moment[i], 'g', 12);
        res += "\n";
    }
    return "Моменты весовой функции\n" + res;
}

QString Integrator::getInfoAboutIndexForOrth()
{
    QString res = QString("Ортогональный многочлен:\n")
            + QString("x^2+")
            + QString::number(c1, 'g', 12)
            + "x+"
            + QString::number(c2, 'g', 12)
            + "\n";
    return res;
}

QString Integrator::getInfoAboutNodes()
{
    return "Узлы КФ НАСТ:\n"
            + QString::number(x1, 'g', 12)
            + ", "
            + QString::number(x2, 'g', 12)
            + "\n";
}

QString Integrator::getInfoAboutIndexForPoli()
{
    return "Коэффициенты КФ НАСТ:\n"
            + QString::number(A1, 'g', 12)
            + ", "
            + QString::number(A2, 'g', 12)
            + "\n";
}

QString Integrator::getinfoAboutCheck()
{
    return "\nРезультат проверки для f(x)=x^3:\nТочное значение интеграла: "
            + QString::number(checkCorr, 'g', 12)
            + "\n"
            + "Значение интеграла по формуле: "
            + QString::number(checkCalc, 'g', 12)
            + "\nПогрешность: "
            + QString::number(checkCorr - checkCalc, 'g', 12)
            + "\n";
}
