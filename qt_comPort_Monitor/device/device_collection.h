#ifndef DEVICE_COLLECTION_H
#define DEVICE_COLLECTION_H

#include <QObject>
#include <QHash>

class Device;
class Sensor_Collection;

class Device_Collection : public QObject
{
    Q_OBJECT

    QHash<QString, Device*> m_devicesCollection{};   //list of identified devices
    Sensor_Collection* m_sensorCollection;
public:
    explicit Device_Collection(QObject *parent = nullptr);
    Sensor_Collection* sensorCollection() const;

public slots:
    //get appropriated device with updated values
    void parseMessage(QString const& portName, QString const& message);
    void removeDevice(QString const& deviceName);

signals:
    void createForm(Device* device, QStringList const& param, QString const& portName);
};

#endif // DEVICE_COLLECTION_H
