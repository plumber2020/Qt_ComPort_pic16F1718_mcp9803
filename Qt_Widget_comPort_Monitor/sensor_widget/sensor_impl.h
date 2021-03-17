#ifndef SENSOR_IMPL_H
#define SENSOR_IMPL_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSerialPort>

#include "../config_widget/config.h"


class Sensor_Impl : public QObject
{
    Q_OBJECT

    QString m_portName{};
    QString m_sensorID{};
    QSerialPort *serial;
    int error_parse_count{ERROR_COUNT_LIMIT};

public:
    explicit Sensor_Impl(QString portName, QObject *parent = nullptr);

signals:
    void paramIdentified(QStringList);
    void valueChanged(float);
    void dataChanged(QString);
    void finished();

public slots:
    void waitingData();

private:
    void do_parse(QString data);
};

#endif // SENSOR_IMPL_H
