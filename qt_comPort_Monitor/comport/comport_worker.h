#ifndef COMPORT_WORKER_H
#define COMPORT_WORKER_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>

#define WDTimer_MONITORING_INTERVAL_msec 25000


class ComPort_Worker : public QObject
{
    Q_OBJECT
    QSerialPort* port;
    QTimer* wdt;

public:
    explicit ComPort_Worker(QObject *parent = nullptr);
    ~ComPort_Worker();

    QString portName();
    void setPortName(QString const& portName);
    void setParams(qint32 baudrate);

signals:
    void started(QString const& portName);
    void readFromPort(QString const& msg);
    void errorUpdated(QString const& error);
    void finished(QString const& portName);

public slots:
    void openPort(QIODevice::OpenMode mode);
    void writeToPort(QString const&);
    void closePort();

private slots:
    void read_handler();
    void error_handler(QSerialPort::SerialPortError);
};

#endif // COMPORT_WORKER_H
