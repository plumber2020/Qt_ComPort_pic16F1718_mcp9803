#ifndef SENSOR_COLLECTION_H
#define SENSOR_COLLECTION_H

#include <QObject>
#include <QHash>
#include <QFile>

class Sensor_Collection : public QObject
{
    Q_OBJECT
    using Collection_t = QHash<QString, QStringList>;
    Collection_t m_parameters{};     //collection list of sensor parameters

public:
    explicit Sensor_Collection(QObject *parent = nullptr);

    void uploadCollection();                        //get list of sensorNames
    QStringList getParameters(QString const& sensorName) const;

private:
    void load(QString const& fileName, Collection_t &collection);

signals:
    void collectionChanged(QStringList);
};

#endif // SENSOR_COLLECTION_H
