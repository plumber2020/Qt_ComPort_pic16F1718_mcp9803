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
    m_param.measure = params.at(0);
    m_param.unit = params.at(1);
    for (int i=2; i<params.size(); ++i)
        m_param.limits[i-2] = params.at(i).toDouble();

    double& min = m_param.limits.front();
    double& max = m_param.limits.back();

    ui->label_measure->setText(m_param.measure);
    ui->label_unit->setText(m_param.unit);
    ui->label_min->setText(QString("MIN=%1").arg(min));
    ui->label_max->setText(QString("MAX=%1").arg(max));

    ui->progressBar->setMinimum(min);
    ui->progressBar->setMaximum(max);
}

void IndicatorLCD_Form::setValues(const QStringList &values)
{
    double value = values.at(0).toDouble();
    double& min = m_param.limits.front();
    double& max = m_param.limits.back();

    if(value<=max && min<=value) {
        ui->lcdNumber->display(value);
        ui->progressBar->setValue(value);
    }
    else {
        ui->lcdNumber->display("ERROR");
        ui->progressBar->setValue(min);
    }

}
