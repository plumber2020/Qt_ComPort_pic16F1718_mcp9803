#include "formSensor.h"
#include "ui_formSensor.h"
#include <QLCDNumber>
#include <QProgressBar>

#include "indicatorBar.h"
#include "indicatorLCD.h"

FormSensor::FormSensor(IndicatorType indicatortype, QWidget *parent)
    : QWidget(parent)
    , m_indicatortype(indicatortype)
    , ui(new Ui::FormSensor)
{
    ui->setupUi(this);
    switch (indicatortype) {
    case LCD:
        this->setMinimumWidth(400);
        indicator = new IndicatorLCD(this);
        break;
    case BAR:
        this->setMinimumWidth(200);
        indicator = new IndicatorBar(this);
        break;
    }
    ui->verticalLayout->insertWidget(1, indicator, 0, Qt::Alignment());
}

FormSensor::~FormSensor()
{
    delete ui;
}

void FormSensor::on_pushButton_Close_clicked()
{
    emit self_remove(QString("XX__XX"));
}
