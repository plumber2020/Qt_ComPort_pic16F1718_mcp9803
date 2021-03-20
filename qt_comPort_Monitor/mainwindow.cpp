#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/formSensor.h"
#include "widgets/form_SensorCollectionList.h"

#include <QString>
#include <QLayout>
#include <QDebug>

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

    auto *sc = new Form_SensorCollectionList();
    ui->groupBox_Config->layout()->addWidget(sc);
    sc->show();
    sc->uploadCollection();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Add_clicked()
{
    FormSensor *sensor = new FormSensor(LCD);
    connect(sensor, &FormSensor::self_remove, this, &MainWindow::onRemoveSensor);

    sensorlist.append(sensor);
    ui->vLayout_Display->addWidget(sensor);
    sensor->show();
    dynamic_resize();
}
void MainWindow::on_pushButton_Plus_clicked()
{
    if(!sensorlist.empty())
        emit sensorlist.at(0)->displayValue(ui->lineEdit->text());
}

void MainWindow::onRemoveSensor(QString const& str)
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
    this->adjustSize();
    this->resize(this->size());
}



