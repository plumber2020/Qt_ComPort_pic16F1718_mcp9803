#include "indicatorLCD_form.h"
#include "ui_indicatorLCD_form.h"

IndicatorLCD_Form::IndicatorLCD_Form(Indicator *parent) :
    Indicator(parent),
    ui(new Ui::IndicatorLCD_Form)
{
    ui->setupUi(this);
}

IndicatorLCD_Form::~IndicatorLCD_Form()
{
    delete ui;
}


void IndicatorLCD_Form::setParams(QStringList const& param)
{
    m_param = PARAM{param.at(0), param.at(1), param.at(2).toInt(), param.at(3).toInt()};
    ui->label_measure->setText(param.at(0));
    ui->label_unit->setText(param.at(1));
    ui->label_min->setText(QString("MIN=")+param.at(2));
    ui->label_max->setText(QString("MAX=")+param.at(3));

    ui->progressBar->setMinimum(m_param.min);
    ui->progressBar->setMaximum(m_param.max);
}

void IndicatorLCD_Form::setValues(const QStringList &values)
{
    double value = values.at(0).toDouble();

    if(value<=m_param.max && m_param.min<=value) {
        ui->lcdNumber->display(value);
        ui->progressBar->setValue(value);
    }
    else {
        ui->lcdNumber->display("ERROR");
        ui->progressBar->setValue(m_param.min);
    }

}
