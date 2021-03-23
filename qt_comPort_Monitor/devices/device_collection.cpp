#include "device_collection.h"
#include "device.h"
#include "device_config.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDebug>


//const QStringList Device_Collection::deviceTemplateList = {DEVICECOLLECTION_TEMPLATE_LIST};

Device_Collection::Device_Collection(QObject *parent)
    : QObject(parent)
{
}

void Device_Collection::uploadCollection()
{
    int lineCount{};
    QStringList sensorNames;

    QFile file(":/sensorCollection/devices.txt");
    if (!file.exists()) {
        qWarning("Cannot find file");
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning("Cannot access file");
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line[0]==DEVICECOLLECTION_COMMENT_LINE) continue;

        QStringList paramList = line.split(DEVICECOLLECTION_PAR_GROUP_DIVIDER);
        if (paramList.size() ==  0 ) continue;

        QString sensorName = paramList.at(0);
        m_collection.insert(sensorName, paramList);
        sensorNames.append(sensorName);

        qDebug() << line; ++lineCount;
    }
    file.close();

    qDebug("Total lines of sensors: writed = %d, loaded = %d",
           lineCount, m_collection.size());

    emit send_ToSensorNamesBox(qMove(sensorNames));
}

Device *Device_Collection::parseMessage(const QString &message)
{
    QStringList deviceMessage = message.split(DEVICECOLLECTION_MSG_GROUP_DIVIDER);
    if(deviceMessage.size() ==0) return nullptr;

    QString deviceName = deviceMessage.at(0);
    QStringList _name =   deviceMessage.at(0).split(DEVICECOLLECTION_MSG_ADDRESS_DIVIDER);
    QStringList _values = deviceMessage.at(1).split(DEVICECOLLECTION_MSG_VALUES_DIVIDER);
    QStringList _flags =  deviceMessage.at(2).split(DEVICECOLLECTION_MSG_VALUES_DIVIDER);

    if(!m_collection.contains(_name.at(0))) return nullptr;

    Device *device = m_devices.value(deviceName);
    if(!device) {
       device = new Device(deviceName, this);
       m_devices.insert(deviceName, device);
       emit send_ToDeviceNamesBox(deviceName);
    }

    device->setValues(_values);
    device->setFlags(_flags);
    return device;
}

QStringList Device_Collection::getSensor(const QString &deviceName) const
{
    QStringList _name = deviceName.split(DEVICECOLLECTION_MSG_ADDRESS_DIVIDER);
    return m_collection.value(_name.at(0));
}

void Device_Collection::receiveDebug(const QStringList &strlist)
{
    for(QString const& str : strlist)
        qDebug() << str;
}
