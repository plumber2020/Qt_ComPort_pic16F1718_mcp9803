#include "displaygroup_form.h"
#include "ui_displaygroup_form.h"

#include "./device/device_collection.h"
#include "./device/sensor_collection.h"
#include "./widget/device_form.h"
#include "./device/device.h"

#include <QtDebug>

DisplayGroup_Form::DisplayGroup_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayGroup_Form)
{
    ui->setupUi(this);

    m_deviceCollection = new Device_Collection(this);
    m_deviceCollection->sensorCollection()->uploadCollection();

    connect(m_deviceCollection,&Device_Collection::createForm,
            this, &DisplayGroup_Form::makeDeviceForm);
}

DisplayGroup_Form::~DisplayGroup_Form()
{
    delete ui;
}

void DisplayGroup_Form::makeDeviceForm(Device *device, QStringList const& param, QString const& portName)
{
    Device_Form *w = new Device_Form(device, this);
    w->setParameters(param);
    ui->rootLayout->addWidget(w,0,Qt::AlignLeft|Qt::AlignTop);
    m_devicesForm[portName] = w;

    connect(w,&Device_Form::finished, m_deviceCollection, &Device_Collection::removeDevice);
}

void DisplayGroup_Form::removeDeviceForm(const QString &portName)
{
    Device_Form *w = m_devicesForm.take(portName);
    if(w) {
        delete w;
        qDebug() << QString("Device_Form deleted: comport[%1]")
                    .arg(portName);
    }
}

void DisplayGroup_Form::treatMessage(QString const& portName, QString const& message)
{
    m_deviceCollection->parseMessage(portName, message);
}

void DisplayGroup_Form::treatCommand(const QString &command)
{
    qDebug() << "#COMMAND" << "\t" << command;
}
