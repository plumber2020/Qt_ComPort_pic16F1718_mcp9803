#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <QObject>

class Device;
class Sensor_Collection;

class Device_Controller : public QObject
{
    Q_OBJECT
    Sensor_Collection* m_sensorCollection;

public:
    explicit Device_Controller(QObject *parent = nullptr);
    Sensor_Collection* sensorCollection() const;

public slots:
    QStringList parseMessage_getParams(Device* device, QString const& message);
    QStringList parseMessage_getValues(Device* device, QString const& message);

signals:
};

#endif // DEVICE_CONTROLLER_H
