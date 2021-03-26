#include "device_form.h"
#include "ui_device_form.h"

#include "device.h"
#include "device_config.h"
#include "widgets/indicatorLCD.h"
#include "widgets/indicatorFLAGs.h"

Device_Form::Device_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Device_Form)
{
    ui->setupUi(this);
}

Device_Form::~Device_Form()
{
    delete ui;
}

Device *Device_Form::device() const
{
    return m_device;
}

void Device_Form::setDevice(Device *device, QStringList const& sensorParam)
{
    m_device = device;
    device->setParent(this);
    QString deviceName = device->name();

    QString sensorMeasure = sensorParam.at((int)SENSOR_PARAM_NAMES::MEASURE);
    QString sensorUnit = sensorParam.at((int)SENSOR_PARAM_NAMES::UNIT);
    QString sensorFlags = sensorParam.at((int)SENSOR_PARAM_NAMES::FLAGsLIST);

    ui->groupBox->setTitle(deviceName);
    ui->label_Measure->setText(sensorMeasure);
    ui->label_Unit->setText(sensorUnit);

    IndicatorFLAGS *iflg = new IndicatorFLAGS(sensorFlags,this);
    ui->hLayout_2->addWidget(iflg);
    connect(device,&Device::flagsChanged,
            [=](QStringList const& strlist){ iflg->displayToFLAGS(strlist);} );

    IndicatorLCD *ilcd = new IndicatorLCD(this);
    ui->hLayout_2->addWidget(ilcd);
    connect(device,&Device::valuesChanged,
            [=](QStringList const& strlist){ ilcd->display(strlist.at(0));} );

}

