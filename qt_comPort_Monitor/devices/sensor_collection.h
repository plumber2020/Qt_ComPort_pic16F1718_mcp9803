#ifndef SENSOR_COLLECTION_H
#define SENSOR_COLLECTION_H

#include <QObject>
#include <QHash>

class Sensor_Collection : public QObject
{
    Q_OBJECT

    QHash<QString, QStringList> m_collection{};    //collection list of sensors
public:
    explicit Sensor_Collection(QObject *parent = nullptr);

    QStringList uploadCollection();                 //get list of sensorNames
    QStringList getParameters(QString const& sensorName) const;

signals:
    void sendSensorList(QString);
};

#endif // SENSOR_COLLECTION_H
