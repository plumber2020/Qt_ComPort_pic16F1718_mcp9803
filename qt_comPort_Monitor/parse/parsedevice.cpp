#include "parsedevice.h"


ParseDeviceObject::ParseDeviceObject(QObject *parent) : QObject(parent)
{
    lineNames[INDICATOR_TYPES] =
            QStringList{INDICATOR_TYPES_DEFAULT};
    lineNames[SEPARATOR_TYPES] =
            QStringList{SEPARATOR_NAMES_DEFAULT};

    separators[GROUP_SEPARATOR] = QRegExp(QString(GROUPS_SEPARATOR));
    separators[NAMES_SEPARATOR] = QRegExp(QString(GNAMES_SEPARATOR));
    separators[INDIC_SEPARATOR] = QRegExp(QString(INDICS_SEPARATOR));
    separators[PARAM_SEPARATOR] = QRegExp(QString(PARAMS_SEPARATOR));
    separators[VALUE_SEPARATOR] = QRegExp(QString(VALUES_SEPARATOR));

}

bool ParseDeviceObject::isComment(const QString &line) const
{
    return line.startsWith(COMMENT_LINE);
}

void ParseDeviceObject::setConfig(const QString &line)
{
    for (QHash<QString, QStringList>::iterator iter =
         lineNames.begin(); iter != lineNames.end(); ++iter)
    {
        QString _name = QString(COMMENT_LINE).append(iter.key()).append(':');
        if(line.startsWith(_name)) {
            iter.value() = parse(
                    QString(line).remove(_name).trimmed(), VALUE_SEPARATOR);
            break;
        }
    }

    QStringList &separatorNames = lineNames[SEPARATOR_TYPES];
    for (int j=0; j<separatorNames.size(); ++j)
    {
        QString _name = QString(COMMENT_LINE).append(separatorNames.at(j)).append(':');
        if(line.startsWith(_name)) {
            separators[j] = QRegExp(
                QString(line).remove(_name).trimmed());
            break;
        }
    }
}

QStringList &ParseDeviceObject::getIndicators() const
{
    return lineNames[INDICATOR_TYPES];
}

bool ParseDeviceObject::isDataLine(const QString &line) const
{
    return line.size()!=0 && !line.startsWith(COMMENT_LINE);
}

bool ParseDeviceObject::isStartsWith_NAME(const QString &line) const
{
    return line.startsWith("NAME");
}

bool ParseDeviceObject::isStartsWith_VALUE(const QString &line) const
{
    return line.startsWith("VALUE");
}

QString ParseDeviceObject::parse_NAME_line(const QString &line) const
{
/*
NAME:  MCP9800; VALUES: LCD [Temperature °C  -50 125]
*/
    QStringList _group = parse(line,GROUP_SEPARATOR);
    //result--> [0]:{NAME:  MCP9800} [1]:{VALUES: LCD [Temperature °C  -50 125]}

    if(_group.size()==0) return QString();

    QStringList _gpart = parse(_group[0],NAMES_SEPARATOR);
     //result--> [0]:{NAME} [1]:{MCP9800}

    if(_gpart.size()<=1) return QString();

    return _gpart.at(1);
    //return-->MCP9800
}

QStringList ParseDeviceObject::parse_VALUE_line(const QString &line) const
{
/*
VALUE: {LCD} [Temperature  °C   -50  75  80 125]
*/
    QStringList _values{};

    QStringList _param = parse(line, NAMES_SEPARATOR);
    //return-->[0]{VALUE} [1]{{LCD} [Temperature  °C   -50  75  80 125]}

    if(_param.size()<=1) return _values;

    QStringList _paramList = parse(_param[1], INDIC_SEPARATOR);
    //return-->[0]{LCD} [1]{[Temperature  °C   -50  75  80 125]}

    if(_paramList.size()<=1) //
        _paramList.insert(0,QString());


    QString& _indicatorName = _paramList[0];
    if(_paramList.size()<=1) return _values;

    QStringList _measureValues = parse(_paramList[1], PARAM_SEPARATOR);
    //return-->[0]{Temperature  °C   -50  75  80 125}
    if(_measureValues.size()==0) return _values;

    _values << _indicatorName;
    _values << parse(_measureValues[0], VALUE_SEPARATOR);

    return _values;
    //return-->[0]{LCD} [1]{Temperature} [2]{°C} [3]{-50} ...
}

QStringList ParseDeviceObject::parse(const QString &line, SEPARATOR_POSITION pos) const
{
    QRegExp rx = separators.value(pos);
    return line.split(rx, Qt::SkipEmptyParts)
            .filter(QRegExp(QString("^[^%1]").arg(COMMENT_LINE)));
}

