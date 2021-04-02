#include "device.h"
#include "./parse/parsedevice.h"
#include <QDebug>

Device::Device(QString name, QObject *parent)
    : QObject(parent)
    , m_name(name)
{
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
        qDebug() << QString("Device[%1] setValues:").arg(m_name) << values;
        emit valuesChanged(values);
    }
}

QStringList Device::values() const
{
    return m_values;
}

