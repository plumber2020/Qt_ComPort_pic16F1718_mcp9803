#ifndef SENSOR_COLLECTION_H
#define SENSOR_COLLECTION_H

#include <QObject>
#include <QHash>
#include "device_config.h"

class Sensor_Collection : public QObject
{
    Q_OBJECT

    QHash<QString, QStringList> m_collection{};     //collection list of sensors
public:
    explicit Sensor_Collection(QObject *parent = nullptr);

    QStringList uploadCollection();                 //get list of sensorNames
    QString getParameter(QString const& sensorName, PARAM_NAMES paramName) const;

signals:

};

#endif // SENSOR_COLLECTION_H
