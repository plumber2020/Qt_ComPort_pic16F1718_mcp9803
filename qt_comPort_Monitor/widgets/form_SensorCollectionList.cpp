#include "form_SensorCollectionList.h"
#include "ui_form_SensorCollectionList.h"
#include "config.h"
#include "sensor.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QIODevice>
#include <QRegExp>
#include <QTextStream>
#include <QDebug>

Form_SensorCollectionList::Form_SensorCollectionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_SensorCollectionList)
{
    ui->setupUi(this);
}

Form_SensorCollectionList::~Form_SensorCollectionList()
{
    delete ui;
}

void Form_SensorCollectionList::uploadCollection()
{
    int lineCount{};

    QFile file(":/sensorCollection/devices.txt");
    if (!file.exists()) {
        qWarning("Cannot find file");
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning("Cannot access file");
        return;
    }

    QRegExp rx(SENSORCOLLECTION_PARAMETER_GROUP_DIVIDER);

    QTextStream in(&file);
    in.setCodec("UTF-8");

    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->label->setText(ui->label->text() + line + "\n");

        if (line[0]==SENSORCOLLECTION_PARAMETER_COMMENT_LINE) continue;

        QStringList device_list = line.split(rx);
        if (device_list.size() > 0 )
        {
            m_sensorCollectionStrings.insert(device_list.at(0), device_list);
            qDebug() << line;
            Sensor s;
            s.parseParam(device_list);
            m_sensors.insert(device_list.at(0), s);
        }
       ++lineCount;
    }
    file.close();

    qDebug("Total lines of sensors: writed = %d, loaded = %d", lineCount, m_sensors.size());

}


