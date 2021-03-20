#include "sensor.h"
#include "config.h"
#include <QRegExp>
#include <QTextStream>

Sensor::Sensor()
{

}

void Sensor::parseParam(QStringList const& param_list)
{
    QStringList param_name = QString(SENSORCOLLECTION_PARAMETER_TEMPLATE).split(
                                QRegExp(SENSORCOLLECTION_PARAMETER_GROUP_DIVIDER));
    int i = 0;
    for (auto &&name : param_name)
    {
        m_params.insert(name, param_list.at(i++).trimmed());
    }
}

QString Sensor::getParam(QString key)
{
    return m_params.value(key);
}
