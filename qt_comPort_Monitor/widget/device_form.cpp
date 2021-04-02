#include "device_form.h"
#include "ui_device_form.h"
#include "./widget/indicators/LCD/indicatorLCD_form.h"
#include "./device/device.h"

#include <QtDebug>


Device_Form::Device_Form(Device *device, QWidget *parent)
    : QWidget(parent)
    , m_device(device)
    , ui(new Ui::Device_Form)
{
    ui->setupUi(this);

    Indicator* indicator = new IndicatorLCD_Form();
    connect(m_device,&Device::valuesChanged, this,&Device_Form::setValues);
//    connect(m_device,&Device::flagsChanged,  this,&Device_Form::setValues);
    m_indicators.append(indicator);

    ui->rootLayout->addWidget(indicator);

}

Device_Form::~Device_Form()
{
    delete ui;
}

void Device_Form::setParameters(const QStringList &/*param*/)
{
    //distibute params to indicators
    m_indicators.at(0)->setParams(QStringList{"Temperature","°C","0","150"});
}

void Device_Form::setValues(const QStringList &values)
{
    //distibute values to indicators
     m_indicators.at(0)->setValues(values);
}

//#define QREGEXP_DIVIDER_GROUPS  QRegExp("([;]\\s*)")
//#define QREGEXP_DIVIDER_VALUES  QRegExp("([ ]\\s*)")

//void Widget::on_pushButton_clicked()
//{
//    QStringList strlist = ui->lineEdit->text().split(QREGEXP_DIVIDER_GROUPS);
//    if(strlist.size()==0) return;
//        m_indicators.at(0)->setValues(strlist.at(0).split(QREGEXP_DIVIDER_VALUES));
//    if(strlist.size()==1)
//        m_indicators.at(1)->setValues(QStringList(""));
//    else
//        m_indicators.at(1)->setValues(strlist.at(1).split(QREGEXP_DIVIDER_VALUES));
//}
