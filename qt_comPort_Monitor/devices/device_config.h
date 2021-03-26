#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H


#define DEVICECOLLECTION_COMMENT_LINE      "#"

enum class SENSOR_PARAM_NAMES {NAME, MEASURE, UNIT, MIN, MAX, FLAGsLIST};
// parameters example:  MCP9800; Temperature; °C; -50; 125; NORMAL|ALERT, ALARM

// parameter dividers
#define PAR_GROUP_DIVIDER      ";"    // "G1;G2;..." - groups
#define PAR_FLAGS_DIVIDER      ","    // "F1,F2,..." - flags
#define PAR_FLAGSTATE_DIVIDER  "|"    // "A|B|..."   - multistate flag

#define QRegExp_PAR_GROUP_DIVIDER      QRegExp("([" PAR_GROUP_DIVIDER "]\\s*)")     // and any spaces after
#define QRegExp_PAR_FLAGS_DIVIDER      QRegExp("([" PAR_FLAGS_DIVIDER "]\\s*)")     // and any spaces after
#define QRegExp_PAR_FLAGSTATE_DIVIDER  QRegExp("([" PAR_FLAGSTATE_DIVIDER "]\\s*)") // and any spaces after

// message example:     MCP9800:001; 76.2 ...; ALERT ...
enum class DEVICE_VALUE_MESSAGE {FULNAME, VALUES, FLAGS};

// message dividers
#define MSG_GROUP_DIVIDER      ";"    // "G1;G2;..." - groups
#define MSG_ADDRESS_DIVIDER    ":"    // "MCP9800:001" - address=001
#define MSG_VALUES_DIVIDER     " "    // space

#define QRegExp_MSG_GROUP_DIVIDER      QRegExp("([" MSG_GROUP_DIVIDER "]\\s*)")     // and any spaces after
#define QRegExp_MSG_ADDRESS_DIVIDER    QRegExp("([" MSG_ADDRESS_DIVIDER "])")       //
#define QRegExp_MSG_VALUES_DIVIDER     QRegExp("([" MSG_VALUES_DIVIDER "]\\s*)")    // and any spaces after


#endif // DEVICE_CONFIG_H
