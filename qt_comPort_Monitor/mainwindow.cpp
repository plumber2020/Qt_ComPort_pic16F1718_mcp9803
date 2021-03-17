#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/form_sensor.h"
#include <QString>
#include <QLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Something title"));
//    ui->groupBox_Config->layout()->setAlignment(Qt::AlignTop);
//    ui->vLayout_Display->setAlignment(Qt::AlignTop);


    this->adjustSize();
    QSize empty_window_size = this->size();
    QSize full_window_size = empty_window_size + QSize(406,0);
    this->resize(full_window_size);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Add_clicked()
{
    FormSensor *sensor = new FormSensor();
    connect(sensor, &FormSensor::self_remove, this, &MainWindow::remove_Sensor);

    sensorlist.append(sensor);
    ui->vLayout_Display->addWidget(sensor);
    sensor->show();
    dynamic_resize();
}
void MainWindow::on_pushButton_Plus_clicked()
{
    if(!sensorlist.empty())
        sensorlist.at(0)->setValue(ui->lineEdit->text().toDouble());
}

void MainWindow::remove_Sensor(QString const& str)
{
    if (FormSensor* sensor = qobject_cast<FormSensor*>(sender())) {
        if( int i = sensorlist.indexOf(sensor); i!= -1) {
            delete sensor;
            sensorlist.removeAt(i);
        }
    }
    dynamic_resize();
    qDebug() << str << "sensorlist.size()=" << sensorlist.size();
}

void MainWindow::dynamic_resize()
{
    this->update();
    this->adjustSize();
    this->resize(this->size());
}



