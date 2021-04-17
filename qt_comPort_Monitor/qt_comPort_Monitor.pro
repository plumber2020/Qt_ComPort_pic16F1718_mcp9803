QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comport/comport_controller.cpp \
    comport/comport_worker.cpp \
    device/device.cpp \
    device/device_controller.cpp \
    device/sensor_collection.cpp \
    logging/Logger.cpp \
    main.cpp \
    mainwindow.cpp \
    parse/parsedevice.cpp \
    widget/comportgroup_form.cpp \
    widget/device_form.cpp \
    widget/displaygroup_form.cpp \
    widget/indicator.cpp \
    widget/indicators/FLG/indicatorFLG_form.cpp \
    widget/indicators/LCD/indicatorLCD_form.cpp

HEADERS += \
    comport/comport_controller.h \
    comport/comport_worker.h \
    device/device.h \
    device/device_controller.h \
    device/sensor_collection.h \
    logging/Logger.h \
    mainwindow.h \
    parse/parsedevice.h \
    widget/comportgroup_form.h \
    widget/device_form.h \
    widget/displaygroup_form.h \
    widget/indicator.h \
    widget/indicators/FLG/indicatorFLG_form.h \
    widget/indicators/LCD/indicatorLCD_form.h

FORMS += \
    mainwindow.ui \
    widget/comportgroup_form.ui \
    widget/device_form.ui \
    widget/displaygroup_form.ui \
    widget/indicators/FLG/indicatorFLG_form.ui \
    widget/indicators/LCD/indicatorLCD_form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config/sensor_parameters.txt \
    config/sensor_testMessage.txt \
    logging/debug.log

RESOURCES += \
    resources.qrc
