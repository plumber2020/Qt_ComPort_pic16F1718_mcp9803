#include "device_collection.h"
#include "sensor_collection.h"
#include "device.h"
#include "./parse/parsedevice.h"

#include <QDebug>

Device_Collection::Device_Collection(QObject *parent) : QObject(parent)
{
    m_sensorCollection = new Sensor_Collection(parent);
}

Sensor_Collection* Device_Collection::sensorCollection() const
{
    return m_sensorCollection;
}

void Device_Collection::parseMessage(QString const& portName, QString const& message)
{
    //parsing message lines
    //START example:
    //  MCP9803:000; 70.2 ALERT
    //

    ParseDeviceObject pd_object;
    if(!pd_object.isDataLine(message)) return;

    QStringList deviceMessage =
                pd_object.parse(message,ParseDeviceObject::GROUP_SEPARATOR);
    if(deviceMessage.size() <2) return;
    //result--> [0]:{MCP9803:000} [1]:{70.2 ALERT}

    QString deviceName = deviceMessage.at(0);
    QString deviceValues = deviceMessage.at(1);

    Device *device = m_devicesCollection.value(deviceName);
    if(!device)
    {
        QStringList _name =
                pd_object.parse(deviceName,ParseDeviceObject::NAMES_SEPARATOR);
        //result--> [0]:{MCP9803} [2]:{000}
        QString sensorName = _name.at(0);
        QStringList _param = m_sensorCollection->getParameters(sensorName);
        if(_param.size()==0) //no such sensor in collection
             return;

        device = new Device(deviceName,this);
        m_devicesCollection.insert(deviceName, device);

        emit createForm(device, _param, portName);
    }

    QStringList _values = pd_object.parse(deviceValues, ParseDeviceObject::VALUE_SEPARATOR);
    //result--> [0]:{70.2} [1]{ALERT}

    device->setValues(_values);
}

void Device_Collection::removeDevice(QString const& deviceName)
{
    qDebug() << QString("m_devicesCollection.size = [%1]")
                .arg(m_devicesCollection.size());
    Device* device = m_devicesCollection.take(deviceName);
    delete device;
    qDebug() << QString("m_devicesCollection.size = [%1]")
                .arg(m_devicesCollection.size());

}


