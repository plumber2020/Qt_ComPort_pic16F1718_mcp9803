#include "form_sensor.h"
#include "ui_form_sensor.h"

FormSensor::FormSensor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSensor)
{
    ui->setupUi(this);
}

FormSensor::~FormSensor()
{
    delete ui;
}

void FormSensor::setValue(double value)
{
    m_value += value;
    ui->lcdNumber->display(m_value);
}

void FormSensor::on_pushButton_Close_clicked()
{
    emit self_remove(QString("XX__XX"));
}
