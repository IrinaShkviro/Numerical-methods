#include "equidistantinterpolation.h"
#include "equationsolver.h"

equidistantInterpolation::equidistantInterpolation(QWidget *parent):
    QWidget(parent)
  , calculator(new myFunction())
  , mainWindow(new QWidget())
  , mainGrid(new QGridLayout())
{
}

void equidistantInterpolation::getData()
{
    QLabel* degreeLabel = new QLabel("Введите степень интерполяционного многочлена");
    degreeLabel->setWordWrap(true);
    mainGrid->addWidget(degreeLabel, 0, 0);

    degreeLineEdit = new QLineEdit();
    connect(degreeLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_degreeLineEdit_textChanged()));
    mainGrid->addWidget(degreeLineEdit, 0, 1);

    errorDegreeLabel = new QLabel("Степень должна быть целым положительным числом, меньше, чем количество узлов");
    errorDegreeLabel->setWordWrap(true);
    errorDegreeLabel->setStyleSheet("color: rgb(250, 0, 0)");
    errorDegreeLabel->setVisible(false);
    mainGrid->addWidget(errorDegreeLabel, 0, 2);

    interpolationPointLabel = new QLabel("Введите точку интерполяции из интервала от "
                                     + QString::number(startOfInterval, 'g', 12)
                                     + " до "
                                     + QString::number(endOfInterval, 'g', 12)
                                    );
    degreeLabel->setWordWrap(true);

    mainGrid->addWidget(interpolationPointLabel, 1, 0);

    interpolationPointLineEdit = new QLineEdit();
    connect(interpolationPointLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_interpolationPointLineEdit_textChanged()));
    mainGrid->addWidget(interpolationPointLineEdit, 1, 1);

    errorInterpolationPointLabel = new QLabel("Нужно ввести число из заданного диапазона");
    errorInterpolationPointLabel->setWordWrap(true);
    errorInterpolationPointLabel->setStyleSheet("color: rgb(250, 0, 0)");
    errorInterpolationPointLabel->setVisible(false);
    mainGrid->addWidget(errorInterpolationPointLabel, 1, 2);

    calculatePushButton = new QPushButton("Calculate!");
    mainGrid->addWidget(calculatePushButton, 4, 1);
    connect(calculatePushButton,SIGNAL(clicked()), this, SLOT(on_calculate_clicked()));

    mainWindow->setLayout(mainGrid);
    mainWindow->show();

    resultOfInvertedTableLabel = new QLabel();
    resultOfInvertedTableLabel->setWordWrap(true);
    resultOfInvertedTableLabel->setVisible(false);
    mainGrid->addWidget(resultOfInvertedTableLabel, 3, 0, 1, 3);
    errorOfInvertedTableLabel = new QLabel();
    errorOfInvertedTableLabel->setWordWrap(true);
    errorOfInvertedTableLabel->setVisible(false);
    mainGrid->addWidget(errorOfInvertedTableLabel, 4, 0, 1, 3);

    resultOfInvertedEquationLabel = new QLabel();
    resultOfInvertedEquationLabel->setWordWrap(true);
    resultOfInvertedEquationLabel->setVisible(false);
    mainGrid->addWidget(resultOfInvertedEquationLabel, 5, 0, 1, 3);
    errorOfInvertedEquationLabel = new QLabel();
    errorOfInvertedEquationLabel->setWordWrap(true);
    errorOfInvertedEquationLabel->setVisible(false);
    mainGrid->addWidget(errorOfInvertedEquationLabel, 6, 0, 1, 3);

    repeatInvertLabel = new QLabel("Хотите ввести еще одно значение или перейти к задаче численного дифференцирования?");
    repeatInvertLabel->setWordWrap(true);
    repeatInvertLabel->setVisible(false);
    mainGrid->addWidget(repeatInvertLabel, 7, 0, 1, 3);

    repeatInvertButton = new QPushButton("Ввести значение");
    connect(repeatInvertButton, SIGNAL(clicked()), this, SLOT(on_repeatInvertButton_clicked()));
    repeatInvertButton->setVisible(false);
    mainGrid->addWidget(repeatInvertButton, 8, 1);

    fluxionButton = new QPushButton("К задаче численного дифференцирования");
    connect(fluxionButton, SIGNAL(clicked()), this, SLOT(on_fluxionButton_clicked()));
    fluxionButton->setVisible(false);
    mainGrid->addWidget(fluxionButton, 8, 2);

    valueInPointLabel = new QLabel();
    valueInPointLabel->setVisible(false);
    mainGrid->addWidget(valueInPointLabel, 5, 0, 1, 3);

    errorInResultLabel = new QLabel();
    errorInResultLabel->setVisible(false);
    mainGrid->addWidget(errorInResultLabel, 6, 0, 1, 3);

    repeatLabel = new QLabel("Хотите ввести еще одну интерполяционную точку или перейти к задаче обратного интерполирования?");
    repeatLabel->setWordWrap(true);
    repeatLabel->setVisible(false);
    mainGrid->addWidget(repeatLabel, 7, 0, 1, 3);

    repeatButton = new QPushButton("Ввести точку");
    repeatButton->setVisible(false);
    connect(repeatButton, SIGNAL(clicked()), this, SLOT(on_repeatButton_clicked()));
    mainGrid->addWidget(repeatButton, 8, 1);

    newTaskButton = new QPushButton("К задаче обратного интерполирования");
    newTaskButton->setVisible(false);
    connect(newTaskButton, SIGNAL(clicked()), this, SLOT(on_newTaskButton_clicked()));
    mainGrid->addWidget(newTaskButton, 8, 2);
}

double equidistantInterpolation::generateTable(double a, double b, int countOfpoints)
{
    startOfInterval = a;
    endOfInterval = b;
    startOfInvertedInterval = calculator->f(startOfInterval);
    endOfInvertedInterval = calculator->f(endOfInterval);
    countOfPoints = countOfpoints;
    step = (endOfInterval - startOfInterval)/(countOfPoints - 1);
    double x = startOfInterval;
    startValues = new QTableWidget();
    startValues->setRowCount(countOfPoints);
    startValues->setColumnCount(2);
    startValues->setHorizontalHeaderLabels(QStringList() << "x" << "f(x)");
    for (int i = 0; i < countOfPoints; i++) {
        QTableWidgetItem* point = new QTableWidgetItem();
        startData[i][1] = x;
        invertedStartData[i][2] = x;
        point->setText(QString::number(x));
        startValues->setItem(i, 0, point);
        QTableWidgetItem* pointValue = new QTableWidgetItem();
        startData[i][2] = calculator->f(x);
        invertedStartData[i][1] = startData[i][2];
        pointValue->setText(QString::number(startData[i][2]));
        startValues->setItem(i, 1, pointValue);
        x += step;
    }
    startValues->show();
    getData();
    return step;
}

void equidistantInterpolation::on_calculate_clicked()
{
    valueInPointLabel->setVisible(false);
    errorInResultLabel->setVisible(false);
    repeatLabel->setVisible(false);
    repeatButton->setVisible(false);
    newTaskButton->setVisible(false);
    bool ok;
    polinomDegree = degreeLineEdit->text().toInt(&ok);
    if (!ok || polinomDegree <= 1 || polinomDegree >= countOfPoints) {
        errorDegreeLabel->setVisible(true);
        return;
    }
    double interpolationPoint = interpolationPointLineEdit->text().toDouble(&ok);
    if (!ok
            || interpolationPoint < startOfInterval
            || interpolationPoint > endOfInterval
            || interpolationPoint > startOfInterval + step
            && interpolationPoint < startOfInterval + int ((polinomDegree + 1) / 2) * step
        || interpolationPoint > endOfInterval - int ((polinomDegree + 1) / 2) * step
            && interpolationPoint < endOfInterval - step) {
        errorInterpolationPointLabel->setText("Введите число в одном из интервалов: ["
                                                    + QString::number(startOfInterval, 'g', 12)
                                                    + "; "
                                                    + QString::number(startOfInterval + step, 'g', 12)
                                                    + "], ["
                                                    + QString::number(startOfInterval + int ((polinomDegree + 1) / 2) * step, 'g', 12)
                                                    + "; "
                                                    + QString::number(endOfInterval - int ((polinomDegree + 1) / 2) * step, 'g', 12)
                                                    + "], ["
                                                    + QString::number(endOfInterval - step, 'g', 12)
                                                    + "; "
                                                    + QString::number(endOfInterval, 'g', 12)
                                                    + "]");
        errorInterpolationPointLabel->setVisible(true);
        return;

    }

    double result = fullInterpolate(interpolationPoint);

    valueInPointLabel->setText("Значение интерполяционного полинома в точке "
                                     + QString::number(interpolationPoint, 'g', 12)
                                     + " равно "
                                     + QString::number(result, 'g', 12)
                                   + defineCase);
    valueInPointLabel->setVisible(true);

    double errorInResult = calculator->myAbs(calculator->f(interpolationPoint) - result);
    errorInResultLabel->setText("Абсолютная погрешность вычислений "
                                    + QString::number(errorInResult, 'g', 12));
    errorInResultLabel->setVisible(true);
    repeatLabel->setVisible(true);
    repeatButton->setVisible(true);
    newTaskButton->setVisible(true);
}

void equidistantInterpolation::on_repeatButton_clicked()
{
    interpolationPointLineEdit->clear();
    valueInPointLabel->clear();
    errorInResultLabel->clear();
    repeatLabel->clear();
    repeatButton->setVisible(false);
    newTaskButton->setVisible(false);
}

void equidistantInterpolation::on_newTaskButton_clicked()
{
    interpolationPointLabel->setText("Введите значение функции y из интервала от "
                                         + QString::number(startOfInvertedInterval)
                                         + " до "
                                         + QString::number(endOfInvertedInterval));
    interpolationPointLineEdit->clear();
    invertedInterpolationPointLineEdit = new QLineEdit();
    connect(interpolationPointLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_invertedInterpolationPointLineEdit_textChanged()));
    mainGrid->addWidget(interpolationPointLineEdit, 1, 1);
    errorInInvertedIntervalLabel = new QLabel("Нужно ввести число из заданного диапазона");
    errorInInvertedIntervalLabel->setWordWrap(true);
    errorInInvertedIntervalLabel->setStyleSheet("color: rgb(250, 0, 0)");
    errorInInvertedIntervalLabel->setVisible(false);
    mainGrid->addWidget(errorInInvertedIntervalLabel, 1, 2);

    valueInPointLabel->clear();
    errorInResultLabel->clear();
    repeatLabel->clear();
    repeatButton->setVisible(false);
    newTaskButton->setVisible(false);
    calculatePushButton->setVisible(false);

    calculateInvertedButton = new QPushButton("Calculate!");
    connect(calculateInvertedButton, SIGNAL(clicked()), this, SLOT(on_calculateInvertedButton_clicked()));
    mainGrid->addWidget(calculateInvertedButton, 2, 1);
}

void equidistantInterpolation::on_calculateInvertedButton_clicked()
{
    bool ok;
    polinomDegree = degreeLineEdit->text().toInt(&ok);
    if (!ok || polinomDegree <= 1 || polinomDegree >= countOfPoints) {
        errorDegreeLabel->setVisible(true);
        return;
    }

    double y = interpolationPointLineEdit->text().toDouble(&ok);
    if (!ok
            || y < startOfInvertedInterval && y < endOfInvertedInterval
            || y > endOfInvertedInterval && y > startOfInvertedInterval)
    {
        errorInInvertedIntervalLabel->setVisible(true);
        return;
    }

    double resultOfInvertedTable = calculateInvertedTable(y);
    resultOfInvertedTableLabel->setText("Значение аргумента, высчитанное с помощью перевернутой таблицы равно "
                                       + QString::number(resultOfInvertedTable, 'g', 12));
    resultOfInvertedTableLabel->setVisible(true);
    errorOfInvertedTableLabel->setText("Абсолютная величина невязки с этом случае "
                                           + QString::number(calculator->myAbs(calculator->f(resultOfInvertedTable) - y), 'g', 12));
    errorOfInvertedTableLabel->setVisible(true);

    EquationSolver* bijectionSolver = new EquationSolver(this);
    double resultOfInvertedEquation = bijectionSolver->bijectionMethod(startOfInterval, endOfInterval, y);
    resultOfInvertedEquationLabel->setText("Значение аргумента, высчитанное с помощью решения уравнения равно "
                                       + QString::number(resultOfInvertedEquation, 'g', 12));
    resultOfInvertedEquationLabel->setVisible(true);
    errorOfInvertedEquationLabel->setText("Абсолютная величина невязки с этом случае "
                                           + QString::number(calculator->myAbs(calculator->f(resultOfInvertedEquation) - y), 'g', 12));
    errorOfInvertedEquationLabel->setVisible(true);

    repeatInvertLabel->setText("Хотите ввести еще одно значение или перейти к задаче численного дифференцирования?");
    repeatInvertLabel->setVisible(true);
    repeatInvertButton->setVisible(true);
    fluxionButton->setVisible(true);
}

double equidistantInterpolation::calculateInvertedTable(double invertedPoint)
{
    for (int i = 0; i < countOfPoints; i++) {
        invertedStartData[i][0] = calculator->myAbs(invertedPoint - invertedStartData[i][1]);
    }
    qsortStartData(0, countOfPoints - 1);

    for (int i = 0; i < polinomDegree; i++) {
        for (int j = 0; j < polinomDegree - i; j++) {
            invertedStartData[j][i + 3] = (invertedStartData[j + 1][i + 2] - invertedStartData[j][i + 2]) / (invertedStartData[j + i + 1][1] - invertedStartData[j][1]);
        }
    }
    double res = 0;
    double mul = 1;
    for (int i = 0; i < polinomDegree + 1; i++) {
        res += invertedStartData[0][i + 2] * mul;
        mul *= (invertedPoint - invertedStartData[i][1]);
    }
    return res;
}

void equidistantInterpolation::qsortStartData(int left, int right)
{
    int i,j;
    double reserv, c, y;
    i = left;
    j = right;
    c = invertedStartData[(left+right) / 2][0];
    while (j >= i) {
        while (invertedStartData[i][0] < c) {
            i ++;
        }
        while (invertedStartData[j][0] > c) {
            j --;
        }
        if (i <= j) {
            y = invertedStartData[i][0];
            invertedStartData[i][0] = invertedStartData[j][0];
            invertedStartData[j][0] = y;
            reserv = invertedStartData[i][1];
            invertedStartData[i][1] = invertedStartData[j][1];
            invertedStartData[j][1] = reserv;
            reserv = invertedStartData[i][2];
            invertedStartData[i][2] = invertedStartData[j][2];
            invertedStartData[j][2] = reserv;
            i ++;
            j --;
        }
    }
    if (left < j) {
        qsortStartData(left, j);
    }
    if (i < right) {
        qsortStartData(i , right);
    }
}

void equidistantInterpolation::on_degreeLineEdit_textChanged()
{
    errorDegreeLabel->setVisible(false);
}

void equidistantInterpolation::on_interpolationPointLineEdit_textChanged()
{
    errorInterpolationPointLabel->setVisible(false);
}

void equidistantInterpolation::on_invertedInterpolationPointLineEdit_textChanged()
{
    errorInInvertedIntervalLabel->setVisible(false);
}

void equidistantInterpolation::on_repeatInvertButton_clicked()
{
    interpolationPointLineEdit->clear();
    resultOfInvertedTableLabel->setVisible(false);
    errorOfInvertedTableLabel->setVisible(false);
    resultOfInvertedEquationLabel->setVisible(false);
    errorOfInvertedEquationLabel->setVisible(false);
    repeatInvertLabel->setVisible(false);
    repeatInvertButton->setVisible(false);
    fluxionButton->setVisible(false);
}

void equidistantInterpolation::on_fluxionButton_clicked()
{
    for (int i = 0; i < 4; i ++) {
        startValues->insertColumn(i + 2);
    }
    startValues->setHorizontalHeaderLabels(QStringList() << "x" << "f(x)"
                                           << "f'(x)" << "|f'(x) - f'(x)correct|"
                                           << "f''(x)" << "|f''(x) - f''(x)correct|");
    for (int i = 1; i < countOfPoints - 1; i++) {
        QTableWidgetItem* flux = new QTableWidgetItem();
        double fluxion = (startData[i + 1][2] - startData[i - 1][2]) / (2 * step);
        flux->setText(QString::number(fluxion, 'g', 12));
        startValues->setItem(i, 2, flux);

        QTableWidgetItem* errInFlux = new QTableWidgetItem();
        double errInFluxion = calculator->myAbs(fluxion
                                                - calculator->fFluxion(startData[i][1]));
        errInFlux->setText(QString::number(errInFluxion, 'g', 12));
        startValues->setItem(i, 3, errInFlux);

        QTableWidgetItem* doubleFlux = new QTableWidgetItem();
        double doubleFluxion = (startData[i + 1][2] + startData[i - 1][2]
                - 2 * startData[i][2]) / (step * step);
        doubleFlux->setText(QString::number(doubleFluxion, 'g', 12));
        startValues->setItem(i, 4, doubleFlux);

        QTableWidgetItem* errInDoubleFlux = new QTableWidgetItem();
        double errDoubleInFluxion = calculator->myAbs(doubleFluxion
                                                - calculator->fDoubleFluxion(startData[i][1]));
        errInDoubleFlux->setText(QString::number(errDoubleInFluxion, 'g', 12));
        startValues->setItem(i, 5, errInDoubleFlux);
    }

    QTableWidgetItem* fluxA = new QTableWidgetItem();
    double fluxionA = (-3 * startData[0][2] + 4 * startData[1][2] - startData[2][2]) / (2 * step);
    fluxA->setText(QString::number(fluxionA, 'g', 12));
    startValues->setItem(0, 2, fluxA);

    QTableWidgetItem* errInFluxA = new QTableWidgetItem();
    double errInFluxionA = calculator->myAbs(fluxionA
                                            - calculator->fFluxion(startData[0][1]));
    errInFluxA->setText(QString::number(errInFluxionA, 'g', 12));
    startValues->setItem(0, 3, errInFluxA);

    QTableWidgetItem* fluxB = new QTableWidgetItem();
    double fluxionB = (3 * startData[countOfPoints - 1][2]
            - 4 * startData[countOfPoints - 2][2] + startData[countOfPoints - 3][2])
            / (2 * step);
    fluxB->setText(QString::number(fluxionB, 'g', 12));
    startValues->setItem(countOfPoints - 1, 2, fluxB);

    QTableWidgetItem* errInFluxB = new QTableWidgetItem();
    double errInFluxionB = calculator->myAbs(fluxionB
            - calculator->fFluxion(startData[countOfPoints - 1][1]));
    errInFluxB->setText(QString::number(errInFluxionB, 'g', 12));
    startValues->setItem(countOfPoints - 1, 3, errInFluxB);
}

double equidistantInterpolation::fullInterpolate(double interpolationPoint)
{
    for (int i = 0; i < polinomDegree; i++) {
        for (int j = 0; j < countOfPoints - i; j++) {
            startData[j][i + 3] = (startData[j + 1][i + 2] - startData[j][i + 2]);
        }
    }
    return interpolate(interpolationPoint);
}

double equidistantInterpolation::interpolate(double interpolationPoint)
{
    if (interpolationPoint <= startData[1][1]) {
        double t = (interpolationPoint - startData[0][1]) / step;
        double res = startData[0][2];
        double mul = 1;
        for (int i = 0; i < polinomDegree; i++) {
            mul *= (t - i) / (i + 1);
            res += startData[0][i + 3] * mul;
        }
        defineCase = " (интерполирование в начале таблицы)";
        return res;
    }

    if (interpolationPoint >= startData[countOfPoints - 2][1]) {
        double t = (interpolationPoint - startData[countOfPoints - 1][1]) / step;
        double res = startData[countOfPoints - 1][2];
        double mul = 1;
        for (int i = 0; i < polinomDegree; i++) {
            mul *= (t + i) / (i + 1);
            res += startData[countOfPoints - i - 2][i + 3] * mul;
        }
        defineCase = " (интерполирование в конце таблицы)";
        return res;
    }

    int shift = -1;
    double startValue = startData[0][1];
    while (startValue <= interpolationPoint) {
        startValue += step;
        shift ++;
    }
    startValue -= step;

    double t = (interpolationPoint - startValue) / step;
    double res = startData[shift][2];
    double mul = 1;
    int sign = -1;
    for (int i = 0; i < polinomDegree; i++) {
        sign *= -1;
        mul *= (t + sign * int ((i + 1) / 2)) / (i + 1);
        res += startData[shift - int ((i + 1) / 2)][i + 3] * mul;
    }
    defineCase = " (интерполирование в середине таблицы)";
    return res;
}
