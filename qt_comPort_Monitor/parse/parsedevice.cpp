#include "parsedevice.h"


ParseDeviceObject::ParseDeviceObject(QObject *parent) : QObject(parent)
{
    lineNames[GROUPNAME_TYPES] =
            QStringList{GROUPNAME_TYPES_DEFAULT};
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

void ParseDeviceObject::config(const QString &line)
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

bool ParseDeviceObject::isDataLine(const QString &line) const
{
    return line.size()!=0 && !line.startsWith(COMMENT_LINE);
}

bool ParseDeviceObject::isFirstLine_ofParams(const QString &line) const
{
    return line.startsWith(lineNames.value(GROUPNAME_TYPES).at(0));
}

QStringList ParseDeviceObject::parse(const QString &line, SEPARATOR_POSITION pos)
{
    QRegExp rx = separators.value(pos);
    return line.split(rx, Qt::SkipEmptyParts);
}

