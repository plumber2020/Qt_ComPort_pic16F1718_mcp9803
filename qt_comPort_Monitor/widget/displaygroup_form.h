#ifndef DISPLAYGROUP_FORM_H
#define DISPLAYGROUP_FORM_H

#include <QWidget>
#include <QHash>

namespace Ui { class DisplayGroup_Form; }
class Device;


class DisplayGroup_Form : public QWidget
{
    Q_OBJECT
    class Device_Collection*  m_deviceCollection;
    QHash<QString, class Device_Form*> m_devicesForm;

public:
    explicit DisplayGroup_Form(QWidget *parent = nullptr);
    ~DisplayGroup_Form();

signals:

public slots:
    void makeDeviceForm(Device *device, QStringList const& param, QString const& portName);
    void removeDeviceForm(QString const& portName);
    void treatMessage(QString const& portName, QString const& message);
    void treatCommand(QString const& command);

private:
    Ui::DisplayGroup_Form *ui;
};

#endif // DISPLAYGROUP_FORM_H
