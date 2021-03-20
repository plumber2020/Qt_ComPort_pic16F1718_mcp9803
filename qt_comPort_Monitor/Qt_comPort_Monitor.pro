QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    widgets/formSensor.cpp \
    widgets/form_SensorCollectionList.cpp \
    widgets/indicatorBar.cpp \
    widgets/indicatorLCD.cpp \
    widgets/sensor.cpp

HEADERS += \
    mainwindow.h \
    widgets/config.h \
    widgets/formSensor.h \
    widgets/form_SensorCollectionList.h \
    widgets/indicatorBar.h \
    widgets/indicatorLCD.h \
    widgets/sensor.h

FORMS += \
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
