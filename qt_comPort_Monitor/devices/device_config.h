#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H


enum PARAM_NAMES {NAME, MEASURE, UNIT, MIN, MAX, FLAGS};

// devices list template names
#define DEVICECOLLECTION_TEMPLATE_LIST     "NAME","MEASURE","UNIT","MIN","MAX","FLAGS"
#define DEVICECOLLECTION_COMMENT_LINE      "#"

// parameters example:  MCP9800; Temperature; °C; -50; 125; NORMAL|ALERT, ALARM
// parameter dividers
#define DEVICECOLLECTION_PAR_GROUP_DIVIDER      QRegExp("([;]\\s*)")    // "G1;G2;..." - groups
#define DEVICECOLLECTION_PAR_FLAGS_DIVIDER      QRegExp("([,]\\s*)")    // "F1,F2,..." - flags
#define DEVICECOLLECTION_PAR_FLAGSTATE_DIVIDER  QRegExp("([|]\\s*)")    // "A|B|..."   - multistate flag

// message example:     MCP9800:001; 76.2; ALERT
// message dividers
#define DEVICECOLLECTION_MSG_GROUP_DIVIDER      QRegExp("([;]\\s*)")    // "G1;G2;..." - groups
#define DEVICECOLLECTION_MSG_ADDRESS_DIVIDER    QRegExp("([:])")        // "MCP9800:001" - address=001
#define DEVICECOLLECTION_MSG_VALUES_DIVIDER     QRegExp("(\\s+)")       // one or more spaces


#endif // DEVICE_CONFIG_H
