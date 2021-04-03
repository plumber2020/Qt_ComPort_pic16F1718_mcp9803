#ifndef DEVICE_FORM_H
#define DEVICE_FORM_H

#include <QWidget>
#include <QList>


//QT_BEGIN_NAMESPACE
namespace Ui { class Device_Form; }
//QT_END_NAMESPACE

class Device_Form : public QWidget
{
    Q_OBJECT
    class Device *m_device;
    QList<class Indicator*> m_indicators;

public:
    Device_Form(Device *device, QWidget *parent = nullptr);
    ~Device_Form();

    void setParameters(QStringList const&);
    void setValues(QStringList const&);

private:
    Ui::Device_Form *ui;
};
#endif // DEVICE_FORM_H
