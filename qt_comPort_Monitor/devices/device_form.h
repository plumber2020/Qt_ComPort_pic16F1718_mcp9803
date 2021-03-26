#ifndef DEVICE_FORM_H
#define DEVICE_FORM_H

#include <QWidget>


namespace Ui {
class Device_Form;
}

class Device_Form : public QWidget
{
    Q_OBJECT

    class Device *m_device;
public:
    explicit Device_Form(QWidget *parent = nullptr);
    ~Device_Form();

    Device *device() const;
    void setDevice(Device *device, QStringList const& sensorParam);

signals:
    void displayValue(QString const&);
    void displayFlags(QString const&);
    //void self_remove(Device*);

private:
    Ui::Device_Form *ui;
};

#endif // DEVICE_FORM_H
