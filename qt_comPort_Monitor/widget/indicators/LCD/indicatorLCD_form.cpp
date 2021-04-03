#include "indicatorLCD_form.h"
#include "ui_indicatorLCD_form.h"


IndicatorLCD_Form::IndicatorLCD_Form(QWidget *parent) :
    Indicator(parent),
    ui(new Ui::IndicatorLCD_Form)
{
    ui->setupUi(this);
}

IndicatorLCD_Form::~IndicatorLCD_Form()
{
    delete ui;
}


void IndicatorLCD_Form::setParams(QStringList const& params)
{
    QString const& measure = params[0];
    QString const& unit = params[1];

    QList<double> temp;
    for (int i=2; i<params.size(); ++i)
        temp.append(params.at(i).toDouble());
    if(temp.size())
        limits = temp;

    double& min = limits.front();
    double& max = limits.back();

    ui->label_measure->setText(measure);
    ui->label_unit->setText(unit);
    ui->label_min->setText(QString("MIN=%1").arg(min));
    ui->label_max->setText(QString("MAX=%1").arg(max));

    ui->progressBar->setRange(min,max);
}

void IndicatorLCD_Form::setValue(const QString &value)
{
    double data = value.toDouble();
    double& min = limits.front();
    double& max = limits.back();

    if(data<=max && min<=data) {
        ui->lcdNumber->display(data);
        ui->progressBar->setValue(data);
    }
    else {
        ui->lcdNumber->display("ERROR");
        ui->progressBar->setValue((data<min)?min:max);
    }

}
