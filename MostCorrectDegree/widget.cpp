#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
  , myIntegrator(new Integrator())
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    double integral = myIntegrator->calcIntegral();
    QString moments = myIntegrator->getInfoAboutMoments();
    QString orthPoli = myIntegrator->getInfoAboutIndexForOrth();
    QString nodes = myIntegrator->getInfoAboutNodes();
    QString indexForPoli = myIntegrator->getInfoAboutIndexForPoli();
    QString check = myIntegrator->getinfoAboutCheck();
    QLabel* resLabel = new QLabel("Промежуточные вычисления:\n"
                                  + moments
                                  + orthPoli
                                  + nodes
                                  + indexForPoli
                                  + check
                                  + "\n"
                                  + "Приближенное значение интеграла:\n"
                                  + QString::number(integral, 'g', 12));
    resLabel->setWordWrap(true);
    ui->firstLayout->addWidget(resLabel, 1, 0, 1, 3);
}
