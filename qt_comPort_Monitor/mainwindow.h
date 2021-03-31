#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QMap>
#include <QPair>
#include <QString>

#include "devices/device_collection.h"
#include "devices/sensor_collection.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    class Form_SensorCollectionList *sc;

    QMap<class Device*, class Device_Form*> m_devicesMAP;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dynamic_resize();


public slots:
    void onRemoveSensor(QString const&);

private slots:
    void on_pushButton_Add_clicked();
    void on_pushButton_Plus_clicked();

    void addForm_SensorCollectionList();

    void add_deviceCollection();
    void on_pButton_com1_clicked();
    void on_pButton_com2_clicked();

private:
    Ui::MainWindow *ui;

    Device_Collection *dc;

};
#endif // MAINWINDOW_H
