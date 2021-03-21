#include "formSensor.h"
#include "ui_formSensor.h"
#include <QLCDNumber>
#include <QProgressBar>

FormSensor::FormSensor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormSensor)
{
    ui->setupUi(this);
}

FormSensor::~FormSensor()
{
    delete ui;
}

void FormSensor::addIndicator(QWidget *indicator)
{
    ui->hLayout_2->addWidget(indicator, 0, Qt::Alignment());
}

void FormSensor::setDeviceName(const QString &name)
{
    m_deviceName = name;
    ui->groupBox->setTitle(name);
}

void FormSensor::setParameters(const QString &measure, const QString &unit)
{
    ui->label_Measure->setText(measure);
    ui->label_Unit->setText(unit);
}

void FormSensor::doFlagsCommand(const QString &command)
{
    ui->label_Command->setText(QString("command:")+command);
}

void FormSensor::on_pushButton_Close_clicked()
{
    emit self_remove(m_deviceName);
}
