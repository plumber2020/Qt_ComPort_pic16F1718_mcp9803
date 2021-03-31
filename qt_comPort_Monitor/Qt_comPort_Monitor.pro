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
    widgets/indicators/BAR/indicatorBar.cpp \
    widgets/indicators/FLAG/flagElement.cpp \
    widgets/indicators/FLAG/flagcolorbutton.cpp \
    widgets/indicators/FLAG/indicatorFLAGs.cpp \
    widgets/indicators/LCD/indicatorLCD.cpp \
    widgets/indicators/indicator.cpp

HEADERS += \
    devices/device_form.h \
    mainwindow.h \
    devices/device.h \
    devices/device_collection.h \
    devices/device_config.h \
    devices/sensor_collection.h \
    widgets/indicators/BAR/indicatorBar.h \
    widgets/indicators/FLAG/flagColorButton.h \
    widgets/indicators/FLAG/flagElement.h \
    widgets/indicators/FLAG/indicatorFLAGs.h \
    widgets/indicators/LCD/indicatorLCD.h \
    widgets/indicators/indicator.h

FORMS += \
    devices/device_form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    sensors-txt-file/sensorDevices.txt
