#ifndef DEVICE_COLLECTION_H
#define DEVICE_COLLECTION_H

#include <QObject>
#include <QHash>

class Device;
class Sensor_Collection;

class Device_Collection : public QObject
{
    Q_OBJECT

    Sensor_Collection *m_sensorCollection;
    QHash<QString, Device*> m_devices{};                //list of identified devices
public:
    explicit Device_Collection(QObject *parent = nullptr);

    Sensor_Collection *sensorCollection() const;
    Device* parseMessage(QString const& message);       //get appropriated device with updated values

signals:
    void devicesChanged(QStringList);

};

#endif // DEVICE_COLLECTION_H
