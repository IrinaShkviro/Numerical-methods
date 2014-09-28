#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->errorIntervalLabel->setVisible(false);
    ui->errorMaxDegreeLabel->setVisible(false);
    ui->errorIntervalIsNegativeLabel->setVisible(false);
}

Widget::~Widget()
{
    delete ui;
}

double Widget::f(double x)
{
    return qSqrt(x);
}

void Widget::on_readyForMakeTable_clicked()
{
    bool ok;
    countOfPoints = ui->maxDegree->toPlainText().toInt(&ok, 10) + 1;
    if (!ok || countOfPoints <= 0) {
        ui->errorMaxDegreeLabel->setVisible(true);
        return;
    }
    QLocale::setDefault(QLocale::German);
    double a, b;
    a = ui->valuesFrom->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->errorIntervalLabel->setVisible(true);
        return;
    }
    b = ui->valuesTo->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->errorIntervalLabel->setVisible(true);
        return;
    }
    if (a >= b) {
        ui->errorIntervalIsNegativeLabel->setVisible(true);
        return;
    }
    double x = a;
    double step = (b - a)/(countOfPoints - 1);
    QTableWidget *startValues = new QTableWidget();
    startValues->setRowCount(countOfPoints);
    startValues->setColumnCount(2);
    startValues->setHorizontalHeaderLabels(QStringList() << "x" << "f(x)");
    for (int i = 0; i < countOfPoints; i++) {
        QTableWidgetItem* point = new QTableWidgetItem();
        startData[i][1] = x;
        point->setText(QString::number(x));
        startValues->setItem(i, 0, point);
        QTableWidgetItem* pointValue = new QTableWidgetItem();
        startData[i][2] = f(x);
        pointValue->setText(QString::number(startData[i][2]));
        startValues->setItem(i, 1, pointValue);
        x += step;
    }
    startValues->show();

    degreeWindow = new QWidget();

    degreeLayout = new QGridLayout();

    QLabel* degreeLabel = new QLabel("Введите максимальную степень полинома");
    degreeLabel->setWordWrap(true);
    degreeLayout->addWidget(degreeLabel, 0, 0);

    degreeLineEdit = new QLineEdit();
    degreeLayout->addWidget(degreeLineEdit, 0, 1);

    errorDegreeLabel = new QLabel("Степень должна быть целым положительным числом");
    errorDegreeLabel->setWordWrap(true);
    errorDegreeLabel->setStyleSheet("color: rgb(250, 0, 0)");
    errorDegreeLabel->setVisible(false);
    degreeLayout->addWidget(errorDegreeLabel, 0, 2);
    connect(degreeLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_degree_textChanged()));

    QLabel* pointLabel = new QLabel("Введите точку x");
    pointLabel->setWordWrap(true);
    degreeLayout->addWidget(pointLabel, 1, 0);

    pointLineEdit = new QLineEdit();
    degreeLayout->addWidget(pointLineEdit, 1, 1);

    errorInterpolationPointLabel = new QLabel("Введенные символы не являются числовыми");
    errorInterpolationPointLabel->setWordWrap(true);
    errorInterpolationPointLabel->setStyleSheet("color: rgb(250, 0, 0)");
    errorInterpolationPointLabel->setVisible(false);
    degreeLayout->addWidget(errorInterpolationPointLabel, 1, 2);
    connect(pointLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_interpolationPoint_textChanged()));

    QLabel* chooseMethodLabel = new QLabel("Выберите метод рассчета");
    chooseMethodLabel->setWordWrap(true);
    degreeLayout->addWidget(chooseMethodLabel, 2, 0, 3, 2);

    lagrangeMethodButton = new QRadioButton("Метод Лагранжа");
    degreeLayout->addWidget(lagrangeMethodButton, 2, 1);

    newtonMethodButton = new QRadioButton("Метод Ньютона");
    degreeLayout->addWidget(newtonMethodButton, 3, 1);

    errorMethodIsNotChoosenLabel = new QLabel("Метод не выбран");
    errorMethodIsNotChoosenLabel->setWordWrap(true);
    errorMethodIsNotChoosenLabel->setStyleSheet("color: rgb(250, 0, 0)");
    errorMethodIsNotChoosenLabel->setVisible(false);
    degreeLayout->addWidget(errorMethodIsNotChoosenLabel, 2, 2);
    connect(lagrangeMethodButton, SIGNAL(clicked()), this, SLOT(on_radioButton_checked()));
    connect(newtonMethodButton, SIGNAL(clicked()), this, SLOT(on_radioButton_checked()));

    QPushButton* calculatePushButton = new QPushButton("Calculate!");
    degreeLayout->addWidget(calculatePushButton, 4, 1);
    connect(calculatePushButton,SIGNAL(clicked()), this, SLOT(on_calculate_clicked()));

    resultLabel = new QLabel("Значение полинома в точке x");
    degreeLayout->addWidget(resultLabel, 5, 0);
    resultLabel->setVisible(false);

    degreeWindow->setLayout(degreeLayout);
    degreeWindow->show();
}

double Widget::myAbs(double x)
{
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

void Widget::on_calculate_clicked()
{
    bool ok;
    polinomDegree = degreeLineEdit->text().toInt(&ok);
    if (!ok || polinomDegree <= 0) {
        errorDegreeLabel->setVisible(true);
        return;
    }
    interpolationPoint = pointLineEdit->text().toDouble(&ok);
    if (!ok) {
        errorInterpolationPointLabel->setVisible(true);
        return;
    }
    if (!newtonMethodButton->isChecked() && !lagrangeMethodButton->isChecked()) {
        errorMethodIsNotChoosenLabel->setVisible(true);
        return;
    }
    for (int i = 0; i < countOfPoints; i++) {
        startData[i][0] = myAbs(interpolationPoint - startData[i][1]);
    }
    qsortStartData(0, countOfPoints - 1);

    resultLabel->setVisible(true);
    QLineEdit* resultLine = new QLineEdit();

    if (lagrangeMethodButton->isChecked()) {
        resultLine->setText(QString::number(lagrangeMethod(interpolationPoint)));
    }
    else {
        resultLine->setText(QString::number(newtonMethod(interpolationPoint)));
    }

    degreeLayout->addWidget(resultLine, 5, 1);
}

void Widget::qsortStartData(int left, int right)
{
    int i,j;
    double reserv, c, y;
    i = left;
    j = right;
    c = startData[(left+right) / 2][0];
    while (j >= i) {
        while (startData[i][0] < c) {
            i ++;
        }
        while (startData[j][0] > c) {
            j --;
        }
        if (i <= j) {
            y = startData[i][0];
            startData[i][0] = startData[j][0];
            startData[j][0] = y;
            reserv = startData[i][1];
            startData[i][1] = startData[j][1];
            startData[j][1] = reserv;
            reserv = startData[i][2];
            startData[i][2] = startData[j][2];
            startData[j][2] = reserv;
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

double Widget::lagrangeMethod(double x)
{
    double res = 0;
    for (int k = 0; k < polinomDegree + 1; k++) {
        res += startData[k][2] * w(x, k) / w(startData[k][1], k);
    }
    return res;
}

double Widget::w(double x, int k)
{
    double res = 1;
    for (int i = 0; i < polinomDegree + 1; i ++) {
        if (i == k) {
            continue;
        }
        res *= (x - startData[i][1]);
    }
    return res;
}

double Widget::newtonMethod(double x)
{
    for (int i = 0; i < polinomDegree; i++) {
        for (int j = 0; j < polinomDegree - i; j++) {
            startData[j][i + 3] = (startData[j + 1][i + 2] - startData[j][i + 2]) / (startData[j + i + 1][1] - startData[j][1]);
        }
    }
    double res = 0;
    double mul = 1;
    for (int i = 0; i < polinomDegree + 1; i++) {
        res += startData[0][i + 2] * mul;
        mul *= (x - startData[i][1]);
    }
    return res;
}

void Widget::on_maxDegree_textChanged()
{
    ui->errorMaxDegreeLabel->setVisible(false);
}

void Widget::on_valuesFrom_textChanged()
{
    ui->errorIntervalLabel->setVisible(false);
    ui->errorIntervalIsNegativeLabel->setVisible(false);
}

void Widget::on_valuesTo_textChanged()
{
    ui->errorIntervalLabel->setVisible(false);
    ui->errorIntervalIsNegativeLabel->setVisible(false);
}

void Widget::on_degree_textChanged()
{
    errorDegreeLabel->setVisible(false);
}

void Widget::on_interpolationPoint_textChanged()
{
    errorInterpolationPointLabel->setVisible(false);
}

void Widget::on_radioButton_checked()
{
    errorMethodIsNotChoosenLabel->setVisible(false);
}
