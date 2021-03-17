#ifndef FORM_SENSOR_H
#define FORM_SENSOR_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QThread>


namespace Ui {
class Form_Sensor;
}

class Form_Sensor : public QWidget
{
    Q_OBJECT

    class Sensor_Impl *m_sensor;
    QThread *th;
public:
    explicit Form_Sensor(QWidget *parent = nullptr);
    explicit Form_Sensor(QString const& portName, QWidget *parent = nullptr);

    ~Form_Sensor();
signals:
    void print_Data(QString const&);
    void finished();

public slots:
    void SET_Parameters(QStringList);
    void LCD_Display(double value);
    void process();

private:
    Ui::Form_Sensor *ui;
};

#endif // FORM_SENSOR_H
