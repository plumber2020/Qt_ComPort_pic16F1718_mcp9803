#include "sensor_impl.h"
#include "../config_widget/comport_manager.h"
#include "../config_widget/sensor_collection.h"
#include "../port_emulator/arduino_emulport.h"

#include <QDebug>
#define DEBUG_SENSOR(name)  qDebug() << "Port[" << name << "]: "


Sensor_Impl::Sensor_Impl(QString portName, QObject *parent)
    : QObject(parent), m_portName(portName)
{
}

void Sensor_Impl::waitingData()
{
    if (m_portName == Arduino_EmulPort::portName())
        serial = new Arduino_EmulPort(this);
    else {
        serial = new QSerialPort(m_portName, this);
        ComPort_Manager::apply_ArduinoPortParameters(serial);
    }

    DEBUG_SENSOR(m_portName) << "is created.";


    auto _IsOpen = [&, this](){
        if (serial) {
            if (auto ptr = dynamic_cast<Arduino_EmulPort*>(serial)) return ptr->isOpen();
            else return serial->isOpen();
        } else
            return false;
    };
    auto _ReadAll = [&, this](){
        if (auto ptr = dynamic_cast<Arduino_EmulPort*>(serial))
            return ptr->readAll();
        else
            return serial->readAll();
    };

    if (serial->isOpen()) {
        DEBUG_SENSOR(m_portName) << "is JUST OPENED! ...finishing...";
        emit finished();
        return;
    }

    DEBUG_SENSOR(m_portName) << "do open ...";
    if (!serial->open(QIODevice::ReadOnly | QIODevice::Text)) {
        DEBUG_SENSOR(m_portName) << "is not open!";
        return;
    }

    while (_IsOpen()) {
        if (serial->waitForReadyRead(DATA_WAITING_DELAY)) {
            DEBUG_SENSOR(m_portName) << "readData ... ...";
            do_parse(_ReadAll());
        } else {
            DEBUG_SENSOR(m_portName) << "timeout of waiting. Device is closing the port ...";
            emit dataChanged("timeout of waiting. Device is closing the port ...");
            serial->close();
        }
    }

    emit finished();
}

void Sensor_Impl::do_parse(QString data)
{
    emit dataChanged(data);

    QStringList data_list = data.split(" ");
    QString sensorID = data_list.at(0);
    QStringList sensorFullParam = Sensor_Collection::get_SensorFullString(sensorID);

    auto error_parse_checking = [&, this]
    {
        if(--error_parse_count != 0) {
            DEBUG_SENSOR(m_portName) << "error_parse: waiting next transmision ...";
            emit dataChanged("error_parse: waiting next transmision ...");
        }
        else {
            DEBUG_SENSOR(m_portName) << "error_parse_count == 0. Device is closing the port ...";
            emit dataChanged("error_parse_count == 0. Device is closing the port ...");
            serial->close();
        }
    };

    //no appropriate sensorID
    if(sensorFullParam.size() == 0) {
        DEBUG_SENSOR(m_portName) << "no appropriate sensorID ...";
        error_parse_checking();
        return;
    }

    //sensorID is identified
    if(m_sensorID != sensorID) {
        if (m_sensorID.size() != 0) {
            DEBUG_SENSOR(m_portName) << "sensorID reading error";
            error_parse_checking();
            return;
        } else {
            DEBUG_SENSOR(m_portName) << "sensor is identified at first time";
            m_sensorID = sensorFullParam.at(0);
            emit paramIdentified(sensorFullParam);
        }
    }

    DEBUG_SENSOR(m_portName) << "value = " << data_list.at(1);
    emit valueChanged(data_list.at(1).toFloat());
}



//void ComPort_Manager::readSerial()
//{
//    /*
//     * readyRead() doesn't guarantee that the entire message will be received all at once.
//     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
//     *
//     */
//    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

//    //  Check to see if there less than 3 tokens in buffer_split.
//    //  If there are at least 3 then this means there were 2 commas,
//    //  means there is a parsed temperature value as the second token (between 2 commas)
//    if(buffer_split.length() < 3){
//        // no parsed value yet so continue accumulating bytes from serial in the buffer.
//        serialData = arduino->readAll();
//        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
//        serialData.clear();
//    }else{
//        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
//        serialBuffer = "";
//        qDebug() << buffer_split << "\n";
//        parsed_data = buffer_split[1];
//        temperature_value = (9/5.0) * (parsed_data.toDouble()) + 32; // convert to fahrenheit
//        qDebug() << "Temperature: " << temperature_value << "\n";
//        parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
//        Dialog::updateTemperature(parsed_data);
//    }

//}
