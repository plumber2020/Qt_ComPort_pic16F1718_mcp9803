#include "device_controller.h"
#include "sensor_collection.h"
#include "device.h"
#include "./parse/parsedevice.h"

#include <QDebug>

Device_Controller::Device_Controller(QObject *parent) : QObject(parent)
{
    m_sensorCollection = new Sensor_Collection(parent);
}

Sensor_Collection* Device_Controller::sensorCollection() const
{
    return m_sensorCollection;
}

QStringList Device_Controller::parseMessage_getParams(Device *device, const QString &message)
{
    //parsing message lines
    //START example:
    //  MCP9803:000; 70.2 ALERT
    //

    ParseDeviceObject pd_object;
    if(!pd_object.isDataLine(message)) return QStringList();

    QStringList deviceMessage =
                pd_object.parse(message,ParseDeviceObject::GROUP_SEPARATOR);
    if(deviceMessage.size() <2) return QStringList();
    //result--> [0]:{MCP9803:000} [1]:{70.2 ALERT}

    QString deviceName = deviceMessage.at(0);
    device->setName(deviceName);

    QStringList _name =
            pd_object.parse(deviceName,ParseDeviceObject::NAMES_SEPARATOR);
    //result--> [0]:{MCP9803} [2]:{000}
    QString sensorName = _name.at(0);
    QStringList _param = m_sensorCollection->getParameters(sensorName);

    //_param.size()==0 means no such sensor in collection
    return _param;
}

QStringList Device_Controller::parseMessage_getValues(Device *device, const QString &message)
{
    //parsing message lines
    //START example:
    //  MCP9803:000; 70.2 ALERT
    //

    ParseDeviceObject pd_object;
    if(!pd_object.isDataLine(message)) return QStringList();

    QStringList deviceMessage =
                pd_object.parse(message,ParseDeviceObject::GROUP_SEPARATOR);
    if(deviceMessage.size() <2) return QStringList();
    //result--> [0]:{MCP9803:000} [1]:{70.2 ALERT}

    QString deviceName = deviceMessage.at(0);
    QString deviceValues = deviceMessage.at(1);

    if(device->name()!=deviceName) return QStringList();

    QStringList _values = pd_object.parse(deviceValues, ParseDeviceObject::VALUE_SEPARATOR);
    //result--> [0]:{70.2} [1]{ALERT}

    return _values;
}


