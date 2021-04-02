#ifndef DISPLAYGROUP_FORM_H
#define DISPLAYGROUP_FORM_H

#include <QWidget>
#include <QList>

namespace Ui {
class DisplayGroup_Form;
}

class DisplayGroup_Form : public QWidget
{
    Q_OBJECT
    class Device_Collection*  m_deviceCollection;
    QList<class Device_Form*> m_devicesForm;
public:
    explicit DisplayGroup_Form(QWidget *parent = nullptr);
    ~DisplayGroup_Form();

public slots:
    void makeDeviceForm(class Device*, QStringList const& param);
    void messageUpdate(QString const& message);

private:
    Ui::DisplayGroup_Form *ui;
};

#endif // DISPLAYGROUP_FORM_H
