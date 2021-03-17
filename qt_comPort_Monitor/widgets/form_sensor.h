#ifndef FORM_SENSOR_H
#define FORM_SENSOR_H

#include <QWidget>
#include <QString>

namespace Ui {
class FormSensor;
}

class FormSensor : public QWidget
{
    Q_OBJECT
    double m_value = 0;
public:
    explicit FormSensor(QWidget *parent = nullptr);
    ~FormSensor();


signals:
    void self_remove(QString);

public slots:
    void setValue(double value);


private slots:
    void on_pushButton_Close_clicked();

private:
    Ui::FormSensor *ui;
};

#endif // FORM_SENSOR_H
