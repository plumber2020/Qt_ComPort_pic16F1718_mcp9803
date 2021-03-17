#include "form_sensor.h"
#include "ui_form_sensor.h"
#include "sensor_impl.h"
#include "../config_widget/sensor_collection.h"


#include <QDebug>
#define DEBUG_FORMSENSOR(name)  qDebug() << "FormSensor[" << name << "]: "

Form_Sensor::Form_Sensor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Sensor)
{
    ui->setupUi(this);
}

Form_Sensor::Form_Sensor(const QString &portName, QWidget *parent)
    : Form_Sensor(parent)
{
    DEBUG_FORMSENSOR(portName) << "created.";
    m_sensor = new Sensor_Impl(portName);
    connect(m_sensor, &Sensor_Impl::paramIdentified, this, &Form_Sensor::SET_Parameters);
    connect(m_sensor, &Sensor_Impl::valueChanged, this, &Form_Sensor::LCD_Display);
//    connect(m_sensor, &Sensor_Impl::dataChanged, [this](QString const& data) { emit print_Data(data);});
    connect(m_sensor, &Sensor_Impl::dataChanged, this, &Form_Sensor::print_Data);
    connect(m_sensor, &Sensor_Impl::finished, this, &Form_Sensor::finished);
    connect(m_sensor, &Sensor_Impl::finished, this, &Form_Sensor::deleteLater);
}

void Form_Sensor::process()
{
    th = new QThread(this);
    connect(th, &QThread::started, m_sensor, &Sensor_Impl::waitingData);
    connect(m_sensor, &Sensor_Impl::finished, th, &QThread::quit);
    connect(th, &QThread::finished, m_sensor, &Sensor_Impl::deleteLater);

    DEBUG_FORMSENSOR("") << "THREAD created and started.";

    m_sensor->moveToThread(th);
    th->start();
}

void Form_Sensor::LCD_Display(double value)
{
    DEBUG_FORMSENSOR("") << "get new value =" << value;
    ui->lcdNumber->display(value);
}

void Form_Sensor::SET_Parameters(QStringList param)
{
    DEBUG_FORMSENSOR("") << "get parameters";
    if (param.size()){
        ui->groupBox->setTitle(param.at(0));
        ui->sensorName->setText(param.at(1));
        ui->sensorUnit->setText(param.at(2));
        ui->lcdNumber->display("------");
        setEnabled(true);

    }
}

Form_Sensor::~Form_Sensor()
{
    delete ui;
}
