#include "comport_worker.h"

ComPort_Worker::ComPort_Worker(QObject *parent)
    : QObject(parent)
{
    port= new QSerialPort(this);
    connect(port,&QSerialPort::readyRead, this,&ComPort_Worker::read_handler);
    connect(port,&QSerialPort::errorOccurred, this,&ComPort_Worker::error_handler,
            Qt::QueuedConnection);

    wdt = new QTimer(this);
    wdt->setInterval(WDTimer_MONITORING_INTERVAL_msec);
    wdt->callOnTimeout([this] {emit errorUpdated("wdt timeout"); closePort(); });
}

ComPort_Worker::~ComPort_Worker()
{
    QMetaObject::invokeMethod(wdt, "stop");
}


QString ComPort_Worker::portName()
{
    return port->portName();
}

void ComPort_Worker::setPortName(QString const& portName)
{
    port->setPortName(portName);
}

void ComPort_Worker::setParams(qint32 baudrate)
{
    port->setBaudRate(baudrate);    // Скорость передачи данных
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
}

void ComPort_Worker::openPort(QIODevice::OpenMode mode)
{
    if(port->open(mode)) {
        port->clear();
        QMetaObject::invokeMethod(wdt, "start", Qt::QueuedConnection);
        emit started(portName());
    }
}

void ComPort_Worker::writeToPort(const QString &data)
{
    port->write(data.toUtf8());
}

void ComPort_Worker::closePort()
{
    QMetaObject::invokeMethod(wdt, "stop");
    if(port->isOpen()) {
        port->close();
    }
    emit finished(portName());
}

void ComPort_Worker::read_handler()
{
    QMetaObject::invokeMethod(wdt, "start");
    if(port->canReadLine()) {
//        qDebug() << _StatusString("reading") << "; thread=" << this->thread();
/*
 * This function reads a line of ASCII characters from the device,
 * up to a maximum of maxSize - 1 bytes, stores the characters in data,
 * and returns the number of bytes read.
 *
 * If a line could not be read but no error ocurred, this function returns 0.
 * If an error occurs, this function returns the length of what could be read,
 * or -1 if nothing was read.
 *
 * The newline character ('\n') is included in the buffer.
 * If a newline is not encountered before maxSize - 1 bytes are read,
 * a newline will not be inserted into the buffer.
 */
        char buf[256];
        qint64 lineLength = port->readLine(buf, sizeof(buf));
        while (lineLength>0) // the line is available in buf
        {
            emit readFromPort(buf);
            lineLength = port->readLine(buf, sizeof(buf));
        }
    }
}

void ComPort_Worker::error_handler(QSerialPort::SerialPortError error)
{
    //handle I/O errors occurred when a resource becomes unavailable,
    //e.g. when the device is unexpectedly removed from the system.
    emit errorUpdated(port->errorString());
    if(error!=QSerialPort::NoError)
        closePort();
}

