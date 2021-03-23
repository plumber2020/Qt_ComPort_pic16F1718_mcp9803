#ifndef DEVICE_COLLECTION_H
#define DEVICE_COLLECTION_H

#include <QObject>
#include <QHash>

class Device;

class Device_Collection : public QObject
{
    Q_OBJECT
    QHash<QString, QStringList> m_collection{};
    QHash<QString, Device*> m_devices{};
public:
    explicit Device_Collection(QObject *parent = nullptr);

    void uploadCollection();
    QStringList getSensor(const QString &sensorName) const;

    Device* parseMessage(QString const& message);

    //static const QStringList deviceTemplateList;

private:

signals:
    void send_ToSensorNamesBox(QStringList const&);
    void send_ToDeviceNamesBox(QString const&);

public slots:
    void receiveDebug(QStringList const&);
};

#endif // DEVICE_COLLECTION_H
