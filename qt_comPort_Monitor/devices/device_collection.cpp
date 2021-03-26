#include "device_collection.h"
#include "sensor_collection.h"
#include "device.h"
#include "device_config.h"

#include <QRegExp>
#include <QDebug>

Device_Collection::Device_Collection(QObject *parent) : QObject(parent)
{
    m_sensorCollection = new Sensor_Collection(parent);
}

Sensor_Collection *Device_Collection::sensorCollection() const
{
    return m_sensorCollection;
}

Device *Device_Collection::parseMessage(const QString &message)
{
    QStringList deviceMessage = message.split(QRegExp_MSG_GROUP_DIVIDER);
    if(deviceMessage.size() ==0) return nullptr;

    QString deviceName = deviceMessage.at((int)DEVICE_VALUE_MESSAGE::FULNAME);

    Device *device = m_devices.value(deviceName);
    if(!device)
    {
        QStringList _name = deviceName.split(QRegExp_MSG_ADDRESS_DIVIDER);
        if(m_sensorCollection->getParameters(_name.at(0)).size()==0) return nullptr;   //no such sensor in collection
        device = new Device(deviceName,this);
        m_devices.insert(deviceName, device);
        emit devicesChanged(m_devices.keys());  //update devices list
    }
    else
    {
        QStringList _values = deviceMessage.at((int)DEVICE_VALUE_MESSAGE::VALUES)
                .split(QRegExp_MSG_VALUES_DIVIDER);
        QStringList _flags =  deviceMessage.at((int)DEVICE_VALUE_MESSAGE::FLAGS)
                .split(QRegExp_MSG_VALUES_DIVIDER);
        device->setValues(_values);
        device->setFlags(_flags);
    }
    return device;
}


