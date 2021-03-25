#include "device.h"
#include "device_collection.h"

Device::Device(QString name, QObject *parent)
    : QObject(parent)
    , m_name(name)
{
    auto const& casted_parent = qobject_cast<Device_Collection*>(parent);
    connect(this, &Device::valuesChanged,
            casted_parent, &Device_Collection::receiveDebug);
    connect(this, &Device::flagsChanged,
            casted_parent, &Device_Collection::receiveDebug);
}

QString Device::name() const
{
    return m_name;
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
