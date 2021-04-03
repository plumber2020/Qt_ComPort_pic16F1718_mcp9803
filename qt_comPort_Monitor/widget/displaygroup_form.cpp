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

void DisplayGroup_Form::makeDeviceForm(Device *device, const QStringList &param)
{
    Device_Form *w = new Device_Form(device, this);
    w->setParameters(param);
    ui->rootLayout->addWidget(w);
}

void DisplayGroup_Form::messageUpdate(const QString &message)
{
    m_deviceCollection->parseMessage(message);
}

void DisplayGroup_Form::treatCommand(const QString &command)
{
    qDebug() << command;
}
