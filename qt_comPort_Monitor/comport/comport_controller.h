#ifndef COMPORT_CONTROLLER_H
#define COMPORT_CONTROLLER_H

#include "comport_worker.h"
#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QTimer>
#include <QList>


class ComPort_Controller : public QObject
{
    Q_OBJECT
    QList<ComPort_Worker*> m_ports;
    QThread* th;

public:
    explicit ComPort_Controller(QObject *parent = nullptr);
    ~ComPort_Controller();

    //static methods
    static QStringList monitoringComPorts();
    static QString portDescription(const QString &portName);

signals:
    void comportActivated(const QString &portName);
    void comportDisactivated(const QString &portName);
    void comportMessageUpdated(const QString &portName,const QString &msg);
    void comportErrorUpdated(const QString &portName,const QString &error);

public slots:
    void connect_toPort(const QString &portName);
    void disconnect_fromPort(const QString &portName);

private slots:
    void activate(const QString &portName);
    void disactivate(const QString &portName);
    void messageUpdate(const QString &msg);
    void errorUpdate(const QString &error);

};

#endif // COMPORT_CONTROLLER_H
