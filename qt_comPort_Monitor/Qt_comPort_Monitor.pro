QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    devices/device_form.cpp \
    main.cpp \
    mainwindow.cpp \
    devices/device.cpp \
    devices/device_collection.cpp \
    devices/sensor_collection.cpp \
    widgets/flagColorButton.cpp \
    widgets/flagElement.cpp \
    widgets/formSensor.cpp \
    widgets/form_SensorCollectionList.cpp \
    widgets/indicatorBar.cpp \
    widgets/indicatorFLAGs.cpp \
    widgets/indicatorLCD.cpp \
    widgets/sensor.cpp

HEADERS += \
    devices/device_form.h \
    mainwindow.h \
    devices/device.h \
    devices/device_collection.h \
    devices/device_config.h \
    devices/sensor_collection.h \
    widgets/config_regexp.h \
    widgets/flagColorButton.h \
    widgets/flagElement.h \
    widgets/formSensor.h \
    widgets/form_SensorCollectionList.h \
    widgets/indicatorBar.h \
    widgets/indicatorFLAGs.h \
    widgets/indicatorLCD.h \
    widgets/sensor.h

FORMS += \
    devices/device_form.ui \
    mainwindow.ui \
    widgets/formSensor.ui \
    widgets/form_SensorCollectionList.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    sensors-txt-file/sensorDevices.txt
