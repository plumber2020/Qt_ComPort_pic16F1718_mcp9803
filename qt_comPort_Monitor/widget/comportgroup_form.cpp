#include "comportgroup_form.h"
#include "ui_comportgroup_form.h"

#include <QLabel>
#include <QRegExp>

////////////////////////////////////////////////////////////////////////////

void label_AppendString(QLabel* label, QString const& arg1)
{
    QString currentTxt = label->text();
    label->setText(currentTxt.append(arg1+'\n'));
}
void label_RemoveString(QLabel* label, QString const& arg1)
{
    QString currentTxt = label->text();
    label->setText(currentTxt.remove(
                    QRegExp(QString("(%1)[\\r]?[\\n]?").arg(arg1))));
}
void label_AddString(QLabel* label, QString const& arg1, QString const& arg2)
{
    QString messages = (label->text().size()<256) ? label->text() : "";
    label->setText(messages.append(
                       QString("[%1]-> %2").arg(arg1,arg2)));
}

////////////////////////////////////////////////////////////////////////////


ComPortGroup_Form::ComPortGroup_Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ComPortGroup_Form)
{
    ui->setupUi(this);
    m_comportController = new ComPort_Controller(this);

    //initialize timer
    m_ptimerMonitoring = new QTimer(this);
    m_ptimerMonitoring->setInterval(MONITORING_INTERVAL_msec/MONITORING_STEPS);
    m_ptimerMonitoring->callOnTimeout([this]
    {
        static int count = 100;
        if(count>100) {
            m_portAvailable = ComPort_Controller::monitoringComPorts();

            QString currentText = ui->comboBox_portAvailable->currentText();
            ui->comboBox_portAvailable->clear();
            ui->comboBox_portAvailable->addItems(m_portAvailable);
            ui->comboBox_portAvailable->setCurrentText(currentText);

            for(int i=0;i<m_portAvailable.size();++i)
            {
                QString const& portName = m_portAvailable.at(i);
                if(!m_portActivated.contains(portName) &&
                   !m_portDisactivated.contains(portName))
                {
                    m_comportController->connect_toPort(portName);
                }
            }
            count = 0;
        }
        ui->progressBar_monitoring->setValue(count);
        count += 100/MONITORING_STEPS;
    });

    //clear txt
    ui->label_portName_activated->clear();
    ui->label_messages->clear();
    ui->label_errors->clear();
    ui->label_portName_disactivated->clear();


    //initialize comport connections
    connect(m_comportController,&ComPort_Controller::comportActivated,
            [this](QString const& portName){
        label_AppendString(ui->label_portName_activated, portName);
        label_RemoveString(ui->label_portName_disactivated, portName);
        m_portActivated.append(portName);
        m_portDisactivated.removeAll(portName);
    });
    connect(m_comportController,&ComPort_Controller::comportDisactivated,
            [this](QString const& portName){
        label_AppendString(ui->label_portName_disactivated, portName);
        label_RemoveString(ui->label_portName_activated, portName);
        if(ui->label_portName_activated->text().isEmpty())
            ui->label_messages->clear();
        m_portDisactivated.append(portName);
        m_portActivated.removeAll(portName);

        emit portDisactivated(portName);
    });
    connect(m_comportController,&ComPort_Controller::comportMessageUpdated,
            [this](QString const& portName, QString const& msg){
        label_AddString(ui->label_messages, portName, msg);
        emit messageUpdated(portName,msg);
    });
    connect(m_comportController,&ComPort_Controller::comportErrorUpdated,
            [this](QString const& portName, QString const& error){
        label_AddString(ui->label_errors, portName, error+'\n');
    });
}

ComPortGroup_Form::~ComPortGroup_Form()
{
    delete ui;
}

// private slots: ////////////////////////////////////////////////////////////

void ComPortGroup_Form::on_pButton_startMonitoring_clicked()
{
    ui->pButton_startMonitoring->setEnabled(0);
    m_ptimerMonitoring->start();
}

void ComPortGroup_Form::on_pButton_stopMonitoring_clicked()
{
    ui->pButton_startMonitoring->setEnabled(1);
    m_ptimerMonitoring->stop();
}

void ComPortGroup_Form::on_comboBox_portAvailable_currentIndexChanged(const QString &arg1)
{
    ui->label_portChecked->setText(arg1);
    ui->label_description->setText(ComPort_Controller::portDescription(arg1));
}

void ComPortGroup_Form::on_pButton_connect_clicked()
{
    QString currentPortName = ui->label_portChecked->text();
    m_comportController->connect_toPort(currentPortName);
}

void ComPortGroup_Form::on_pButton_disconnect_clicked()
{
    QString currentPortName = ui->label_portChecked->text();
    m_comportController->disconnect_fromPort(currentPortName);
}
