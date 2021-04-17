#ifndef DISPLAYGROUP_FORM_H
#define DISPLAYGROUP_FORM_H

#include <QWidget>
#include <QHash>

namespace Ui { class DisplayGroup_Form; }

class Device_Form;
class Device_Controller;


class DisplayGroup_Form : public QWidget
{
    Q_OBJECT
    Device_Controller*  m_deviceController;
    QHash<QString, Device_Form*> m_devices{};

public:
    explicit DisplayGroup_Form(QWidget *parent = nullptr);
    ~DisplayGroup_Form();

signals:

public slots:
    void removeDeviceForm(QString const& portName);
    void treatMessage(QString const& portName, QString const& message);
    void treatCommand(QString const& command);

private:
    Ui::DisplayGroup_Form *ui;
};

#endif // DISPLAYGROUP_FORM_H
