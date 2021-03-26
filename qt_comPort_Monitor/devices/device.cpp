#include "device.h"
#include "device_config.h"
#include "device_collection.h"

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
    return m_name.split(QRegExp_MSG_ADDRESS_DIVIDER).at(0);
}

void Device::setValues(const QStringList &values)
{
    if(m_values != values)
    {
        m_values = QStringList(values);
        emit valuesChanged(values);
    }
}

void Device::setFlags(const QStringList &flags)
{
    if(m_flags != flags)
    {
        m_flags = flags;
        emit flagsChanged(flags);
    }
}

QStringList Device::values() const
{
    return m_values;
}

QStringList Device::flags() const
{
    return m_flags;
}
