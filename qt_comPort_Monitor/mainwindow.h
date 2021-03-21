#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QString>

#include "widgets/formSensor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QHash<QString,FormSensor*> devicelist;
    class Form_SensorCollectionList *sc;
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
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
