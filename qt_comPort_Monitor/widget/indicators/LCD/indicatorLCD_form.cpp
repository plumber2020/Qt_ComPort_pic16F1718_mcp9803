#include "indicatorLCD_form.h"
#include "ui_indicatorLCD_form.h"
#include <QDebug>

IndicatorLCD_Form::IndicatorLCD_Form(QWidget *parent) :
    Indicator(parent),
    ui(new Ui::IndicatorLCD_Form)
{
    ui->setupUi(this);
}

IndicatorLCD_Form::~IndicatorLCD_Form()
{
    delete ui;
}

void IndicatorLCD_Form::make_command(const QString &value)
{
    emit sendCommand(
                QString("{LCD} [%1 %2]")
                .arg(ui->label_measure->text(),value));
}

void IndicatorLCD_Form::setParams(QStringList const& params)
{
    QString const& measure = params[0];
    QString const& unit = params[1];

    QList<double> temp;
    for (int i=2; i<params.size(); ++i)
        temp.append(params.at(i).toDouble());
    if(temp.size())
        limits = temp;

    double& min = limits.front();
    double& max = limits.back();

    ui->label_measure->setText(measure);
    ui->label_unit->setText(unit);
    ui->label_min->setText(QString("MIN=%1").arg(min));
    ui->label_max->setText(QString("MAX=%1").arg(max));

    ui->progressBar->setRange(min,max);
}

void IndicatorLCD_Form::setValue(const QString &value)
{
    bool ok;
    double data = value.toDouble(&ok);
    if(ok && data == ui->lcdNumber->value()) return;

    double& min = limits.front();
    double& max = limits.back();

    if(ok && data<=max && min<=data) {
        ui->lcdNumber->display(data);
        ui->progressBar->setValue(data);
    }
    else {
        ui->lcdNumber->display("ERROR");
        ui->progressBar->setValue((data<min)?min:max);
        make_command("error");
    }
}
