#include "indicatorFLG_form.h"
#include "ui_indicatorFLG_form.h"

IndicatorFLG_Form::IndicatorFLG_Form(QWidget *parent) :
    Indicator(parent),
    ui(new Ui::IndicatorFLG_Form)
{
    ui->setupUi(this);
    connect(ui->pButton, &QPushButton::clicked, [this] {
        emit sendCommand(
                QString("Command Flag:%1 State:%2")
                .arg(ui->label_name->text(),ui->pButton->text())
        );
    });
}

IndicatorFLG_Form::~IndicatorFLG_Form()
{
    delete ui;
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
    QString btn_text("error");


    if(ok && pos<m_states.size()) {
        if(cuttent_state == pos) return;
        btn_text = m_states.at(pos);
    }
    else {
        if(m_states.contains(value)) {
            ok = true;
            pos = m_states.indexOf(value);
            if(cuttent_state == pos) return;
            btn_text = value;
        } else {
            ok = false;
            pos = -1;
            if(cuttent_state == pos) return;
        }
    }

    //set values
    cuttent_state = pos;
    ui->pButton->setFlat(!ok);
    ui->pButton->setEnabled(ok);
    ui->pButton->setText(btn_text);
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
