#include "device.h"
#include "./parse/parsedevice.h"
#include <QDebug>

Device::Device(QString name, QObject *parent)
    : QObject(parent)
    , m_name(name)
{
}

Device::~Device()
{
    qDebug() << QString("Device deleted: name[%1]")
                .arg(m_name);
}

QString Device::name() const
{
    return m_name;
}

QString Device::sensorName() const
{
    ParseDeviceObject pd_object;
    return pd_object.parse(m_name,ParseDeviceObject::NAMES_SEPARATOR).at(0);
}

void Device::setValues(const QStringList &values)
{
    if(m_values != values)
    {
        m_values = QStringList(values);
        emit valuesChanged(values);
    }
}

QStringList Device::values() const
{
    return m_values;
}

