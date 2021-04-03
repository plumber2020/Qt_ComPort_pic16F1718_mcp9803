#include "sensor_collection.h"
#include "./parse/parsedevice.h"

#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>

Sensor_Collection::Sensor_Collection(QObject *parent) : QObject(parent)
{

}

void Sensor_Collection::uploadCollection()
{
    QString strDebug("#uploadCollection");
    strDebug.append(QString('=').repeated(60-strDebug.size()));
    qDebug() << strDebug;

    load(":/config/sensor_parameters.txt", m_parameters);

    emit collectionChanged(m_parameters.keys());

    qDebug() << strDebug;
    qDebug();
    return;
}

void Sensor_Collection::load(QString const& fileName, Collection_t& collection)
{
    qDebug() << fileName << ":";

    QFile file(fileName);
    if (!file.exists()) {
        qWarning("Cannot find file");
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Cannot access file");
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    ParseDeviceObject pd_object;

    QString sensorName;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(pd_object.isComment(line)) {
            pd_object.setConfig(line);
            continue;
        }
        if(!pd_object.isDataLine(line)) continue;

/*parsing data lines - parameters element
START example:

#
#GROUPS_SEPARATOR:  [;]\s*
#GNAMES_SEPARATOR:  [:]\s*
#INDICS_SEPARATOR:  [{}]\s*
#PARAMS_SEPARATOR:  [\[\]]\s*
#VALUES_SEPARATOR:  [ ]\s*
#
#=======================================================

NAME:  MCP9800; VALUES: LCD [Temperature °C  -50 125]

NAME:  MCP9803;
VALUE: {LCD} [Temperature  °C   -50  75  80 125]
VALUE: {FLG} [ALARM-LEVEL  bool NORMAL ALERT]
*/

        qDebug() << '\t' << line;

        if(pd_object.isStartsWith_NAME(line)) //startWith "NAME:"
            sensorName = pd_object.parse_NAME_line(line);

        if(sensorName.size())
            collection[sensorName]
                    .append(pd_object.parse(line,ParseDeviceObject::GROUP_SEPARATOR));

    //RESULT:
    //  collection
    //  [hash_key] =    MCP9803
    //  [hash_value]    [0]= NAME:   MCP9803;
    //                  [1]= VALUES: Temperature [°C -50 125]
    //                  [2]= FLAGS:  ALARM-LEVEL [NORMAL ALERT]

    }
    file.close();
}

QStringList Sensor_Collection::getParameters(QString const& sensorName) const
{
    return m_parameters.value(sensorName);
}

