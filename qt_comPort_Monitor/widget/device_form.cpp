#include "device_form.h"
#include "ui_device_form.h"
#include "./widget/displaygroup_form.h"
#include "./widget/indicators/LCD/indicatorLCD_form.h"
#include "./device/device.h"
#include "./parse/parsedevice.h"

#include <QtDebug>

Device_Form::Device_Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Device_Form)
{
    ui->setupUi(this);
}

Device_Form::~Device_Form()
{
    delete ui;
}

// public methods /////////////////////////////////////////////////////////////

Device *Device_Form::device()
{
    return m_device;
}

void Device_Form::setDevice(Device *device)
{
    if(m_device)
        delete m_device;
    m_device = device;
    m_device->setParent(this);
    connect(m_device,&Device::valuesChanged,
            this,&Device_Form::setMeasurements);
}

void Device_Form::setParameters(const QStringList &params)
{
    ParseDeviceObject pd_object;

    //distibute params to indicators
    for (int i=0; i<params.size(); ++i)
    {
        if(!pd_object.isStartsWith_VALUE(params[i])) continue;

        QStringList _values = pd_object.parse_VALUE_line(params[i]);
        //return--> [0]{LCD}
        //          [1]{Temperature} [2]{°C} [3]{-50} ...

        QString indicator_typeName = _values.takeAt(0);
        Indicator* indicator = Indicator::makeIndicator(indicator_typeName,this);
        if(!indicator) continue;

        indicator->setParams(_values);

        m_indicators.append(indicator);
        ui->rootLayout->addWidget(indicator);

        connect(indicator,&Indicator::sendCommand,
                [this] (const QString &command)
        {
                qobject_cast<DisplayGroup_Form*>(this->parent())
                ->treatCommand(
                            QString("NAME: %1; VALUE: %2")
                               .arg(m_device->name(),command));
        });
    }

    ui->groupBox->setTitle(m_device->name());
}

void Device_Form::setMeasurements(const QStringList &values)
{
    //distibute values to indicators
    //values goes with strong order

    int indicator_size = m_indicators.size();
    for (int i=0; i<values.size(); ++i) {
        if (i<indicator_size) {
            m_indicators[i]->setValue(values.at(i));
        }
    }
}

