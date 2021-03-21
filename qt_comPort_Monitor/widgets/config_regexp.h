#ifndef CONFIG_REGEXP_H
#define CONFIG_REGEXP_H

#include <QString>
#include <QStringList>
#include <QRegExp>

//SensorCollection ParameterList
#define SENSORCOLLECTION_PARAMETER_TEMPLATE          "NAME;MEASURE;UNIT;MIN;MAX;FLAGS"
#define SENSORCOLLECTION_PARAMETER_COMMENT_LINE      "#"
#define SENSORCOLLECTION_PARAMETER_GROUP_DIVIDER     "([;]\\s*)"    // "G1;G2;..." - groups
#define SENSORCOLLECTION_PARAMETER_FLAGS_DIVIDER     "([,]\\s*)"    // "F1,F2,..." - flags
#define SENSORCOLLECTION_PARAMETER_FLAGstate_DIVIDER "([|]\\s*)"    // "A|B|..."   - multistate flag F1

QStringList parse_onGroups(QString const&);
QStringList parse_onFlags(QString const&);

#define SENSORTRANSMISSION_GROUP_DIVIDER            "(\\s+)"        // "MCP9803:000 72.6 NORMAL"
#define SENSORTRANSMISSION_ADDRESS_DIVIDER          "([:]\\s*)"     // "MCP9803:000"

#define MONITORING_DELAY            10000    //10sec

#define ARDUINO_UNO_VENDOR_ID       9025
#define ARDUINO_UNO_PRODUCT_ID      67
#define ARDUINO_UNO_BAUDRATE        115200





#define DATA_WAITING_DELAY          5000    //5sec
#define ERROR_COUNT_LIMIT           3

#endif // CONFIG_REGEXP_H
