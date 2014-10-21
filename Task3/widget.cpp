#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Widget)
  , interpolation(new equidistantInterpolation())
  , stepLabel(new QLabel())
{
    ui->setupUi(this);
    ui->errorIntervalLabel->setVisible(false);
    ui->errorMaxDegreeLabel->setVisible(false);
    ui->errorIntervalIsNegativeLabel->setVisible(false);
    stepLabel->setWordWrap(true);
    stepLabel->setVisible(false);
    ui->startInfo->addWidget(stepLabel, 5, 0, 1, 3);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_readyForMakeTable_clicked()
{
    ui->errorIntervalIsNegativeLabel->setVisible(false);
    ui->errorIntervalLabel->setVisible(false);
    ui->errorMaxDegreeLabel->setVisible(false);

    bool ok;
    int countOfPoints = ui->maxDegree->toPlainText().toInt(&ok, 10);
    if (!ok || countOfPoints < 2) {
        ui->errorMaxDegreeLabel->setVisible(true);
        return;
    }
    QLocale::setDefault(QLocale::German);

    double a = ui->valuesFrom->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->errorIntervalLabel->setVisible(true);
        return;
    }

    double b = ui->valuesTo->toPlainText().toDouble(&ok);
    if (!ok) {
        ui->errorIntervalLabel->setVisible(true);
        return;
    }
    if (a >= b) {
        ui->errorIntervalIsNegativeLabel->setVisible(true);
        return;
    }

    stepLabel->setText("Для данного диапазона шаг "
                                   + QString::number(interpolation->generateTable(a, b, countOfPoints), 'g', 12));
    stepLabel->setVisible(true);
}
