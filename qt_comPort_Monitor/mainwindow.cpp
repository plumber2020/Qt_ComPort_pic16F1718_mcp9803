#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/config_regexp.h"
#include "widgets/formSensor.h"
#include "widgets/form_SensorCollectionList.h"

#include <QString>
#include <QStringList>
#include <QLayout>
#include <QDebug>
#include <QButtonGroup>

#include "widgets/indicatorBar.h"
#include "widgets/indicatorLCD.h"
#include "widgets/indicatorFLAGs.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Something title"));
    ui->groupBox_Config->layout()->setAlignment(Qt::AlignTop);
    ui->vLayout_Display->setAlignment(Qt::AlignTop);

    ui->vLayout_Display->setSizeConstraint(QLayout::SetMinimumSize);
    dynamic_resize();

    addForm_SensorCollectionList();

    //DEVICES/////////////////////////////////////
    add_deviceCollection();

    static QButtonGroup *bg = new QButtonGroup(this);
    bg->addButton(ui->pButton_com1);
    bg->addButton(ui->pButton_com2);


}

void MainWindow::addForm_SensorCollectionList()
{
    sc = new Form_SensorCollectionList();
    connect(sc, &Form_SensorCollectionList::fillSensorCollectionBox,
            [this](QStringList const& strlist){ ui->comboBox->addItems(strlist);});
    ui->tab_1->layout()->addWidget(sc);
    sc->show();
    sc->uploadCollection();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Add_clicked()
{
    QString message = ui->lineEdit->text();
    QStringList words = message.split(QRegExp(SENSORTRANSMISSION_GROUP_DIVIDER));
    QString deviceName = words.at(0);

    QString sensorName = deviceName.split(QRegExp(SENSORTRANSMISSION_ADDRESS_DIVIDER)).at(0);
    Sensor *sensor = sc->getSensor(sensorName);
    QString sensorMeasure = sensor->getParam("MEASURE");
    QString sensorUnit = sensor->getParam("UNIT");
    QString sensorFlags = sensor->getParam("FLAGS");

    FormSensor *device = new FormSensor(this);
    device->setDeviceName(deviceName);
    device->setParameters(sensorMeasure,sensorUnit);
    device->addIndicator(new IndicatorFLAGS(sensorFlags,device));
    device->addIndicator(new IndicatorLCD(device));

    connect(device, &FormSensor::self_remove, this, &MainWindow::onRemoveSensor);

    devicelist[deviceName] = device;
    ui->vLayout_Display->addWidget(device);
    device->show();
    dynamic_resize();
}

void MainWindow::on_pushButton_Plus_clicked()
{
    QString dataString = ui->lineEdit->text();
    QStringList dataStringList = dataString.split(QRegExp(SENSORTRANSMISSION_GROUP_DIVIDER));

    if(auto sensor = devicelist.value(dataStringList.at(0))) {
        emit sensor->displayValue(dataStringList.at(1));

        emit sensor->displayFlags("idle"); //выкл. всех пропущенных в описании дефолтных
        for (int i=2; i< dataStringList.size(); ++i) {
            emit sensor->displayFlags(dataStringList.at(i));
        }
    }
}

void MainWindow::onRemoveSensor(QString const& deviceName)
{
    if(auto sensor = devicelist.value(deviceName)) {
        delete sensor;
        devicelist.remove(deviceName);
    }



    dynamic_resize();
    //qDebug() << device << "sensorlist.size()=" << devicelist.size();
}

void MainWindow::dynamic_resize()
{
    this->adjustSize();
    this->resize(this->size());
}



#include "devices/device.h"
#include "devices/device_collection.h"
#include "devices/device_config.h"
#include "devices/device_form.h"


void MainWindow::add_deviceCollection()
{
    dc = new Device_Collection(this);

    ui->comboBox_sensorsList->addItems(
                dc->sensorCollection()->uploadCollection());
    connect(dc, &Device_Collection::devicesChanged,
            [this](QStringList const& list){ui->comboBox_devicesList->addItems(list); });
}

void MainWindow::on_pButton_com1_clicked()
{
    Device* device = dc->parseMessage(ui->lineEdit_com1->text());
    if(!device) return;

    if(!m_devicesMAP.contains(device)) {
        Device_Form *deviceForm = new Device_Form(this);

        QString sensorName = device->sensorName();
        QStringList sensorParam = dc->sensorCollection()->getParameters(sensorName);
        deviceForm->setDevice(device,sensorParam);

        m_devicesMAP[device] = deviceForm;
        ui->vLayout_Display->addWidget(deviceForm);
        dynamic_resize();

        //second time for display current values in message
        dc->parseMessage(ui->lineEdit_com1->text());
    }

}

void MainWindow::on_pButton_com2_clicked()
{
    dc->parseMessage(ui->lineEdit_com2->text());
}

