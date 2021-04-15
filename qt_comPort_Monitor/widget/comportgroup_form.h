#ifndef COMPORTGROUP_FORM_H
#define COMPORTGROUP_FORM_H

#include <QWidget>
#include <QTimer>

#include "comport/comport_controller.h"

#define MONITORING_INTERVAL_msec    10000
#define MONITORING_STEPS            25


QT_BEGIN_NAMESPACE
namespace Ui { class ComPortGroup_Form; }
QT_END_NAMESPACE

class ComPortGroup_Form : public QWidget
{
    Q_OBJECT
    ComPort_Controller* m_comportController;
    QTimer* m_ptimerMonitoring;
public:
    ComPortGroup_Form(QWidget *parent = nullptr);
    ~ComPortGroup_Form();

signals:
    void messageUpdated(const QString &portName,const QString &msg);
    void portDisactivated(const QString &portName);

private slots:
    //monitoring
    void on_pButton_startMonitoring_clicked();
    void on_comboBox_portAvailable_currentIndexChanged(const QString &arg1);
    void on_pButton_stopMonitoring_clicked();

    //connect-disconnectPort
    void on_pButton_connect_clicked();
    void on_pButton_disconnect_clicked();

private:
    Ui::ComPortGroup_Form *ui;
};
#endif // COMPORTGROUP_FORM_H
