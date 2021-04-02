#ifndef PARSEDEVICE_H
#define PARSEDEVICE_H

#include <QObject>
#include <QHash>
#include <QRegExp>


#define COMMENT_LINE                "#"

#define GROUPNAME_TYPES             "GROUPNAME_TYPES"
#define INDICATOR_TYPES             "INDICATOR_TYPES"
#define SEPARATOR_TYPES             "SEPARATOR_TYPES"

#define GROUPNAME_TYPES_DEFAULT     "NAME", "VALUE"
#define INDICATOR_TYPES_DEFAULT     "LCD", "FLG"
#define SEPARATOR_NAMES_DEFAULT     "GROUPS_SEPARATOR",\
                                    "GNAMES_SEPARATOR",\
                                    "INDICS_SEPARATOR",\
                                    "PARAMS_SEPARATOR",\
                                    "VALUES_SEPARATOR"

//#define GROUP_SEPARATOR_POSITION    0
//#define NAMES_SEPARATOR_POSITION    1
//#define INDIC_SEPARATOR_POSITION    2
//#define PARAM_SEPARATOR_POSITION    3
//#define VALUE_SEPARATOR_POSITION    4

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
    bool isFirstLine_ofParams(QString const& line) const;

    void config(QString const& line);
    QStringList parse(QString const& line,
                      SEPARATOR_POSITION pos);
private:
    static inline QHash<QString,QStringList> lineNames;
    static inline QHash<int,QRegExp> separators;
};

#endif // PARSEDEVICE_H
