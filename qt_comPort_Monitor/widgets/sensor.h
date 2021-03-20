#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include <QStringList>
#include <QHash>

class Sensor
{
    QHash<QString,QString> m_params{};

public:
    Sensor();
    void parseParam(QStringList const&);
    QString getParam(QString key);

};

#endif // SENSOR_H
