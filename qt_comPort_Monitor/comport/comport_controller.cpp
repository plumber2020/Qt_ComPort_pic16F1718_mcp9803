#include "comport_controller.h"
#include <QSerialPortInfo>
#include <QtAlgorithms>
#include <QDebug>


ComPort_Controller::ComPort_Controller(QObject *parent) : QObject(parent)
{
    th = new QThread(this);
    th->start();
}

ComPort_Controller::~ComPort_Controller()
{
    qDeleteAll(m_ports);
    m_ports.clear();

    th->quit();
    th->wait();
}

// static ////////////////////////////////////////////////////////////

QStringList ComPort_Controller::monitoringComPorts()
{
    QStringList portNames{};
    for (auto&& info : QSerialPortInfo::availablePorts())
        portNames << info.portName();
    return portNames;
}

QString ComPort_Controller::portDescription(QString const& portName)
{
    return QSerialPortInfo(portName).description();
}

// public slots: ////////////////////////////////////////////////////////////

void ComPort_Controller::connect_toPort(QString const& portName)
{
    //define & initialize
    ComPort_Worker* port = new ComPort_Worker();
    port->setPortName(portName);
    port->setParams(QSerialPort::Baud57600);

    //m_port connections
    connect(port,&ComPort_Worker::started,this,&ComPort_Controller::activate);
    connect(port,&ComPort_Worker::finished,this,&ComPort_Controller::disactivate);
    connect(port,&ComPort_Worker::readFromPort,this,&ComPort_Controller::messageUpdate);
    connect(port,&ComPort_Worker::errorUpdated,this,&ComPort_Controller::errorUpdate);

    //add in list
    m_ports.append(port);

    //th connections
    port->moveToThread(th);
    connect(th,&QThread::finished, port,&QObject::deleteLater);
    port->openPort(QIODevice::ReadOnly);
}

void ComPort_Controller::disconnect_fromPort(const QString &portName)
{
    for(auto& port : m_ports) {
        if( portName == port->portName()) {
            port->closePort();
            return;
        }
    }
}

// private slots: ////////////////////////////////////////////////////////////

void ComPort_Controller::activate(const QString &portName)
{
    emit comportActivated(portName);
}

void ComPort_Controller::disactivate(const QString &portName)
{
    ComPort_Worker* port = qobject_cast<ComPort_Worker*>(sender());
    m_ports.removeOne(port);
    delete port;

    emit comportDisactivated(portName);
}

void ComPort_Controller::messageUpdate(const QString &msg)
{
    ComPort_Worker* port = qobject_cast<ComPort_Worker*>(sender());
    emit comportMessageUpdated(port->portName(),msg);
}

void ComPort_Controller::errorUpdate(const QString &error)
{
    ComPort_Worker* port = qobject_cast<ComPort_Worker*>(sender());
    emit comportErrorUpdated(port->portName(), error);
}

