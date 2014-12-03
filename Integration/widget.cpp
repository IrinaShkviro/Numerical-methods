#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->intervalCountErrorLabel->setVisible(false);
    ui->intervalSymbolErrorlabel->setVisible(false);
    ui->intervalBoardErrorLabel->setVisible(false);
    ui->errLLabel->setVisible(false);
    connect(ui->readyForMakeTable, SIGNAL(clicked()), this, SLOT(on_calculateButton_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_calculateButton_clicked()
{
    bool ok;
    countOfIntervals = ui->pointCountText->toPlainText().toInt(&ok, 10);
    if (!ok || countOfIntervals < 1) {
        ui->intervalCountErrorLabel->setVisible(true);
        return;
    }
    QLocale::setDefault(QLocale::German);

    A = ui->lowerBoundText->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->intervalSymbolErrorlabel->setVisible(true);
        return;
    }

    B = ui->topBoardText->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->intervalSymbolErrorlabel->setVisible(true);
        return;
    }
    if (A >= B) {
        ui->intervalBoardErrorLabel->setVisible(true);
        return;
    }

    l = ui->lEdit->toPlainText().toInt(&ok, 10);
    if (!ok || l < 1) {
        ui->intervalCountErrorLabel->setVisible(true);
        return;
    }

    myCalc = new Calculator(A, B, countOfIntervals);
    correctValue = myCalc->correctAntiderivativeValue();
    QLabel* correctResLabel = new QLabel();
    correctResLabel->setWordWrap(true);
    correctResLabel->setText("Точное значение интеграла " + QString::number(correctValue, 'g', 12));
    ui->startInfo->addWidget(correctResLabel, 5, 0, 1, 4);
    createWidget();
}

void Widget::createWidget()
{
    resultTable = new QTableWidget();
    resultTable->setColumnCount(4);
    for (int i = 0; i < 4; i++) {
        resultTable->setColumnWidth(i, 222);
    }
    resultTable->setHorizontalHeaderLabels(QStringList() << "Квадратурная формула"
                                           << "Значение интеграла по этому методу"
                                           << "Модуль разности"
                                           << "Теоретическая погрешность");

    resultTable->setRowCount(12);

    QTableWidgetItem* multQuadrItem = new QTableWidgetItem();
    multQuadrItem->setText("Вычисление интеграла по составным квадратурным формулам");
    resultTable->setItem(0, 0, multQuadrItem);

    QTableWidgetItem* name0 = new QTableWidgetItem();
    name0->setText("Среднего прямоугольника");
    resultTable->setItem(1, 0, name0);

    QTableWidgetItem* name1 = new QTableWidgetItem();
    name1->setText("Трапеции");
    resultTable->setItem(2, 0, name1);

    QTableWidgetItem* name2 = new QTableWidgetItem();
    name2->setText("Симпсона");
    resultTable->setItem(3, 0, name2);

    dval0 = myCalc->integrateMultipleMediumRect();
    QTableWidgetItem* val0 = new QTableWidgetItem();
    val0->setText(QString::number(dval0, 'g', 12));
    resultTable->setItem(1, 1, val0);

    dval1 = myCalc->integrateMultipleTrapeze();
    QTableWidgetItem* val1 = new QTableWidgetItem();
    val1->setText(QString::number(dval1, 'g', 12));
    resultTable->setItem(2, 1, val1);

    dval2 = myCalc->integrateMultipleSympson();
    QTableWidgetItem* val2 = new QTableWidgetItem();
    val2->setText(QString::number(dval2, 'g', 12));
    resultTable->setItem(3, 1, val2);

    QTableWidgetItem* err0 = new QTableWidgetItem();
    err0->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dval0), 'g', 12));
    resultTable->setItem(1, 2, err0);

    QTableWidgetItem* err1 = new QTableWidgetItem();
    err1->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dval1), 'g', 12));
    resultTable->setItem(2, 2, err1);

    QTableWidgetItem* err2 = new QTableWidgetItem();
    err2->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dval2), 'g', 12));
    resultTable->setItem(3, 2, err2);

    increaseIntervalCount();
}

void Widget::increaseIntervalCount()
{
    myCalc = new Calculator(A, B, countOfIntervals*l);

    QTableWidgetItem* multLQuadrItem = new QTableWidgetItem();
    multLQuadrItem->setText("Вычисление интеграла по составным квадратурным формулам для m*l промежутков");
    resultTable->setItem(4, 0, multLQuadrItem);

    QTableWidgetItem* namel0 = new QTableWidgetItem();
    namel0->setText("Среднего прямоугольника");
    resultTable->setItem(5, 0, namel0);

    QTableWidgetItem* namel1 = new QTableWidgetItem();
    namel1->setText("Трапеции");
    resultTable->setItem(6, 0, namel1);

    QTableWidgetItem* namel2 = new QTableWidgetItem();
    namel2->setText("Симпсона");
    resultTable->setItem(7, 0, namel2);

    dvall0 = myCalc->integrateMultipleMediumRect();
    QTableWidgetItem* vall0 = new QTableWidgetItem();
    vall0->setText(QString::number(dvall0, 'g', 12));
    resultTable->setItem(5, 1, vall0);

    dvall1 = myCalc->integrateMultipleTrapeze();
    QTableWidgetItem* vall1 = new QTableWidgetItem();
    vall1->setText(QString::number(dvall1, 'g', 12));
    resultTable->setItem(6, 1, vall1);

    dvall2 = myCalc->integrateMultipleSympson();
    QTableWidgetItem* vall2 = new QTableWidgetItem();
    vall2->setText(QString::number(dvall2, 'g', 12));
    resultTable->setItem(7, 1, vall2);

    QTableWidgetItem* errl0 = new QTableWidgetItem();
    errl0->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dvall0), 'g', 12));
    resultTable->setItem(5, 2, errl0);

    QTableWidgetItem* errl1 = new QTableWidgetItem();
    errl1->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dvall1), 'g', 12));
    resultTable->setItem(6, 2, errl1);

    QTableWidgetItem* errl2 = new QTableWidgetItem();
    errl2->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dvall2), 'g', 12));
    resultTable->setItem(7, 2, errl2);

    QTableWidgetItem* errTeor0 = new QTableWidgetItem();
    errTeor0->setText(QString::number(myCalc->useBase()->myAbs(dvall0 - dval0), 'g', 12));
    resultTable->setItem(5, 3, errTeor0);

    QTableWidgetItem* errTeor1 = new QTableWidgetItem();
    errTeor1->setText(QString::number(myCalc->useBase()->myAbs(dvall1 - dval1), 'g', 12));
    resultTable->setItem(6, 3, errTeor1);

    QTableWidgetItem* errTeor2 = new QTableWidgetItem();
    errTeor2->setText(QString::number(myCalc->useBase()->myAbs(dvall2 - dval2), 'g', 12));
    resultTable->setItem(7, 3, errTeor2);

    moreCorrect();
}

void Widget::moreCorrect()
{
    QTableWidgetItem* rungeItem = new QTableWidgetItem();
    rungeItem->setText("Вычисление интеграла с помощью принципа Рунге");
    resultTable->setItem(8, 0, rungeItem);

    QTableWidgetItem* name0r = new QTableWidgetItem();
    name0r->setText("Среднего прямоугольника");
    resultTable->setItem(9, 0, name0r);

    QTableWidgetItem* name1r = new QTableWidgetItem();
    name1r->setText("Трапеции");
    resultTable->setItem(10, 0, name1r);

    QTableWidgetItem* name2r = new QTableWidgetItem();
    name2r->setText("Симпсона");
    resultTable->setItem(11, 0, name2r);

    double dval0r = dvall0 + (dvall0 - dval0)/(qPow(l, 2) - 1);
    QTableWidgetItem* val0r = new QTableWidgetItem();
    val0r->setText(QString::number(dval0r, 'g', 12));
    resultTable->setItem(9, 1, val0r);

    double dval1r = dvall1 + (dvall1 - dval1)/(qPow(l, 2) - 1);
    QTableWidgetItem* val1r = new QTableWidgetItem();
    val1r->setText(QString::number(dval1r, 'g', 12));
    resultTable->setItem(10, 1, val1r);

    double dval2r = dvall2 + (dvall2 - dval2)/(qPow(l, 4) - 1);
    QTableWidgetItem* val2r = new QTableWidgetItem();
    val2r->setText(QString::number(dval2r, 'g', 12));
    resultTable->setItem(11, 1, val2r);

    QTableWidgetItem* err0r = new QTableWidgetItem();
    err0r->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dval0r), 'g', 12));
    resultTable->setItem(9, 2, err0r);

    QTableWidgetItem* err1r = new QTableWidgetItem();
    err1r->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dval1r), 'g', 12));
    resultTable->setItem(10, 2, err1r);

    QTableWidgetItem* err2r = new QTableWidgetItem();
    err2r->setText(QString::number(myCalc->useBase()->myAbs(correctValue - dval2r), 'g', 12));
    resultTable->setItem(11, 2, err2r);

       resultTable->show();
}
