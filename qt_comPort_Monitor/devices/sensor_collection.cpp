#include "sensor_collection.h"
#include "device_config.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QRegExp>

Sensor_Collection::Sensor_Collection(QObject *parent) : QObject(parent)
{

}

QStringList Sensor_Collection::uploadCollection()
{
    int lineCount{};
    QStringList sensorNames;

    QFile file(":/sensorCollection/devices.txt");
    if (!file.exists()) {
        qWarning("Cannot find file");
        return sensorNames;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning("Cannot access file");
        return sensorNames;
    }


    QTextStream in(&file);
    in.setCodec("UTF-8");

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.size()==0
                || line.startsWith(DEVICECOLLECTION_COMMENT_LINE)) continue;

        QStringList paramList = line.split(QRegExp_PAR_GROUP_DIVIDER);
        if (paramList.size()==1) continue;  //only name without params - not useful

        QString sensorName = paramList.at((int)SENSOR_PARAM_NAMES::NAME);
        m_collection.insert(sensorName, paramList);
        sensorNames.append(sensorName);

        qDebug() << line; ++lineCount;
    }
    file.close();

    qDebug("Total lines of sensors: writed = %d, loaded = %d",
           lineCount, m_collection.size());

    return sensorNames;
}


QStringList Sensor_Collection::getParameters(QString const& sensorName) const
{
    return m_collection.value(sensorName);
}
