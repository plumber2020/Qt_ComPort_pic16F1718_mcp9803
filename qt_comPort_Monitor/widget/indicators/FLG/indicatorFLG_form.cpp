#include "indicatorFLG_form.h"
#include "ui_indicatorFLG_form.h"
#include <QDebug>

IndicatorFLG_Form::IndicatorFLG_Form(QWidget *parent) :
    Indicator(parent),
    ui(new Ui::IndicatorFLG_Form)
{
    ui->setupUi(this);
    connect(ui->pButton, &QPushButton::clicked,
            [this] { make_command(ui->pButton->text());});
}

IndicatorFLG_Form::~IndicatorFLG_Form()
{
    delete ui;
}

void IndicatorFLG_Form::make_command(const QString &value)
{
    emit sendCommand(
                QString("{FLG} [%1 %2]")
                .arg(ui->label_name->text(),value));
}

void IndicatorFLG_Form::setParams(const QStringList &params)
{
    m_states = params;
    QString flagName = m_states.takeAt(0);

    ui->label_name->setText(flagName);
    ui->label_states->setText("");
}

void IndicatorFLG_Form::setValue(const QString &value)
{
    bool ok;
    int pos = value.toUInt(&ok, 10);

    if(ok && pos<m_states.size()) {
        if(cuttent_state == pos) return;
        ui->pButton->setText(m_states.at(pos));
    }
    else {
        if(m_states.contains(value)) {
            ok = true;
            pos = m_states.indexOf(value);
            if(cuttent_state == pos) return;
            ui->pButton->setText(value);
        } else {
            ok = false;
            pos = -1;
            ui->pButton->setText("error");
            make_command("error");
            if(cuttent_state == pos) return;
        }
    }

    //set values
    cuttent_state = pos;
    ui->pButton->setFlat(!ok);
    ui->pButton->setEnabled(ok);
    ui->label_states->setText(
                (pos<0)? QString("")
                       : QString("flag_index=%1").arg((cuttent_state)));

    //change background
    QColor backgroundColor;
    backgroundColor.setHsv(0, (pos)? (255*(pos+1)/m_states.size()): 0, 240);
    QString qss =
               QString("background-color: %1")
               .arg(backgroundColor.name());
    ui->pButton->setStyleSheet(qss);
}
