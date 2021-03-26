#include "indicatorFLAGs.h"
#include "config_regexp.h"
#include "flagElement.h"
#include "formSensor.h"

#include <QGridLayout>
#include <QtDebug>

#include "flagColorButton.h"


IndicatorFLAGS::IndicatorFLAGS(QWidget *parent) : QGroupBox(parent)
{
    setTitle("FLAGS");
    QGridLayout *glayout = new QGridLayout(this);
    setLayout(glayout);
}

IndicatorFLAGS::IndicatorFLAGS(const QString &flags, QWidget *parent) : IndicatorFLAGS(parent)
{
    m_bgroup = new QButtonGroup(this);
    QStringList flagList = parseFlagsList(flags);


    //flags = {"NORMAL|ALERT", "ALARM"}
    for (int i=0; i<flagList.size(); ++i)
    {
        QStringList flagState = parseFlagState(flagList[i]);
        if (flagList.size()==0) continue;

        // 1. flagList = "NORMAL","ALERT"
        // 2. flagList = "","ALARM"

        //auto button = new QPushButton(flag.getFlagCurrentName(),this);
        auto button = new FlagColorButton(new FlagElement(flagState),this);

        m_buttonList.append(button);
        m_bgroup->addButton(button, i);
        qobject_cast<QGridLayout*>(layout())->addWidget(
                    button,i%GRID_ROW_MAX, i/GRID_ROW_MAX, Qt::Alignment());
    }
    //var1.
    connect(m_bgroup, SIGNAL(buttonClicked(int)),
            this, SLOT(selectionButtonChanges(int)));
    //var2.
//    connect(this,&IndicatorFLAGS::commandFromFlagsButton,
//            qobject_cast<FormSensor*>(parent), &FormSensor::doFlagsCommand);

    connect(m_bgroup,
            qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked),
            [this](QAbstractButton *button)
    {
        emit commandFromFlagsButton(button->text());
    });

//    connect(this, &IndicatorFLAGS::displayToFLAGS,
//            [this](const QString &str){displayFlags(str);});


}

void IndicatorFLAGS::displayToFLAGS(const QStringList &strlist)
{
    for(QString const& s : strlist)
        displayFlags(s);
}

void IndicatorFLAGS::selectionButtonChanges(int n)
{
    qDebug("clicked FLAGs #%d",n);
}

void IndicatorFLAGS::displayFlags(const QString &str)
{
    qDebug() << "signal FLAG = " << str;
    auto buttonList = m_bgroup->buttons();
    for (auto& button : buttonList) {
        //bool chanched =
                qobject_cast<FlagColorButton*>(button)->getFlagElement()->changeState(str);

    }
}



QStringList IndicatorFLAGS::parseFlagsList(QString str)
{
    QStringList strList = str.split(QRegExp(SENSORCOLLECTION_PARAMETER_FLAGS_DIVIDER));
    return strList;
}

QStringList IndicatorFLAGS::parseFlagState(QString str)
{
    QStringList strList = str.split(QRegExp(SENSORCOLLECTION_PARAMETER_FLAGstate_DIVIDER));
    if (strList.size()==1) strList.insert(0,"idle");
    return strList;
}
