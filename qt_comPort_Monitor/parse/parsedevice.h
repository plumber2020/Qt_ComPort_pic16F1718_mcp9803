#ifndef PARSEDEVICE_H
#define PARSEDEVICE_H

#include <QObject>
#include <QHash>
#include <QRegExp>


#define COMMENT_LINE                "#"                 //not able to change
#define GROUPNAME_TYPES_DEFAULT     "NAME", "VALUE"     //not able to change

#define INDICATOR_TYPES             "INDICATOR_TYPES"
#define SEPARATOR_TYPES             "SEPARATOR_TYPES"

#define INDICATOR_TYPES_DEFAULT     "LCD", "FLG"
#define SEPARATOR_NAMES_DEFAULT     "GROUPS_SEPARATOR",\
                                    "GNAMES_SEPARATOR",\
                                    "INDICS_SEPARATOR",\
                                    "PARAMS_SEPARATOR",\
                                    "VALUES_SEPARATOR"

#define GROUPS_SEPARATOR            "[;]\\s*"
#define GNAMES_SEPARATOR            "[:]\\s*"
#define INDICS_SEPARATOR            "[{}]\\s*"
#define PARAMS_SEPARATOR            "[\\[\\]]\\s*"
#define VALUES_SEPARATOR            "[ ]\\s*"



//////////////////////////////////////////////////////////////////

class ParseDeviceObject : public QObject
{
    Q_OBJECT

public:
    enum SEPARATOR_POSITION {
        GROUP_SEPARATOR = 0,
        NAMES_SEPARATOR, INDIC_SEPARATOR,
        PARAM_SEPARATOR, VALUE_SEPARATOR };


public:
    ParseDeviceObject(QObject *parent = nullptr);

    bool isComment(QString const& line) const;
    bool isDataLine(QString const& line) const;

    bool isStartsWith_NAME(const QString &line) const;
    bool isStartsWith_VALUE(const QString &line) const;

    QString parse_NAME_line(const QString &line) const;
    QStringList parse_VALUE_line(const QString &line) const;

    void setConfig(QString const& line);
    QStringList& getIndicators() const;
    QStringList parse(QString const& line, SEPARATOR_POSITION pos) const;
private:
    static inline QHash<QString,QStringList> lineNames;
    static inline QHash<int,QRegExp> separators;
};

#endif // PARSEDEVICE_H
