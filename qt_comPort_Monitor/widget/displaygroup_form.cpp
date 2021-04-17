#include "displaygroup_form.h"
#include "ui_displaygroup_form.h"

#include "./device/device_controller.h"
#include "./device/sensor_collection.h"
#include "./widget/device_form.h"
#include "./device/device.h"

#include <QtDebug>

DisplayGroup_Form::DisplayGroup_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGroup_Form)
{
    ui->setupUi(this);

    m_deviceController = new Device_Controller(this);
    m_deviceController->sensorCollection()->uploadCollection();

}

DisplayGroup_Form::~DisplayGroup_Form()
{
    delete ui;
}

void DisplayGroup_Form::removeDeviceForm(const QString &portName)
{
    Device_Form *deviceform = m_devices.take(portName);
    if(deviceform) {
        delete deviceform;
        qDebug() << QString("DeviceForm deleted, port[%1]").arg(portName);
    }
}

void DisplayGroup_Form::treatMessage(QString const& portName, QString const& message)
{
    Device_Form* deviceform = m_devices.value(portName);


    if(!deviceform ) {
        Device *device = new Device;
        QStringList param = m_deviceController->parseMessage_getParams(device, message);

        if(device->name().isEmpty() || param.isEmpty())
            return;

        qDebug() << QString("DeviceForm created, port[%1]").arg(portName);
        qDebug() << QString("m_devices.size()=[%1]").arg(m_devices.size());
        deviceform = new Device_Form(this);
        deviceform->setDevice(device);
        deviceform->setParameters(param);
        ui->rootLayout->addWidget(deviceform,0,Qt::AlignLeft|Qt::AlignTop);
        m_devices.insert(portName, deviceform);
    }

    deviceform->device()->setValues(
                m_deviceController->parseMessage_getValues(deviceform->device(), message));
}

void DisplayGroup_Form::treatCommand(const QString &command)
{
    qDebug() << "#COMMAND" << "\t" << command;
}
