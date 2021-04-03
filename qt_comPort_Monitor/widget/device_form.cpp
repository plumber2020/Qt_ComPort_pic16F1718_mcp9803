#include "device_form.h"
#include "ui_device_form.h"
#include "./widget/indicators/LCD/indicatorLCD_form.h"
#include "./device/device.h"
#include "./widget/displaygroup_form.h"
#include "./parse/parsedevice.h"

#include <QtDebug>


Device_Form::Device_Form(Device *device, QWidget *parent)
    : QWidget(parent)
    , m_device(device)
    , ui(new Ui::Device_Form)
{
    ui->setupUi(this);
}

Device_Form::~Device_Form()
{
    delete ui;
}

void Device_Form::setParameters(const QStringList &params)
{
    ParseDeviceObject pd_object;
    //distibute params to indicators
    for (int i=0; i<params.size(); ++i)
    {
        if(!pd_object.isStartsWith_VALUE(params[i])) {
            QString _name = pd_object.parse_NAME_line(params[i]);
            ui->groupBox->setTitle(_name);
            continue;
        }

        QStringList _values = pd_object.parse_VALUE_line(params[i]);
        //return--> [0]{LCD}
        //          [1]{Temperature} [2]{°C} [3]{-50} ...

        Indicator* indicator = Indicator::makeIndicator(_values.takeAt(0),this);
        if(!indicator) continue;

        indicator->setParams(_values);
        connect(m_device,&Device::valuesChanged, this,&Device_Form::setValues);
        m_indicators.append(indicator);
        ui->rootLayout->addWidget(indicator);

        connect(indicator,&Indicator::sendCommand,
                qobject_cast<DisplayGroup_Form*>(this->parent()),
                &DisplayGroup_Form::treatCommand);
    }
}

void Device_Form::setValues(const QStringList &values)
{
    //distibute values to indicators
    //values goes with strong order

    int indicator_size = m_indicators.size();
    for (int i=0; i<values.size(); ++i) {
        if (i<indicator_size)
            m_indicators[i]->setValue(values.at(i));
    }
}

