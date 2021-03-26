#include "indicatorFLAGs.h"
#include "flagElement.h"
#include "flagColorButton.h"

#include <QGridLayout>
#include <QtDebug>


IndicatorFLAGS::IndicatorFLAGS(QWidget *parent) : QGroupBox(parent)
{
    setTitle("FLAGS");
    QGridLayout *glayout = new QGridLayout(this);
    setLayout(glayout);

    m_bgroup = new QButtonGroup(this);
    connect(m_bgroup, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked),
            [=](QAbstractButton *button){
        emit commandFromFlags(QString("COMMAND: ") + button->text());
        //Debug
        qDebug() << QString::asprintf("output command: FLAG[%d] ", m_bgroup->id(button)) << button->text();
    });
}

// Examples of QStringList &flagStates:
// 1. flagList = "NORMAL","ALERT" (default state = flagStates[0] = "NORMAL")
// 2. flagList = "ALARM" (no default state, means "")

void IndicatorFLAGS::addFlagStates(const QStringList &flagStates)
{
    if (flagStates.size()==0) return;

    int i = m_bgroup->buttons().size();
    auto button = new FlagColorButton(new FlagElement(flagStates),this);
    m_bgroup->addButton(button, i);

    qobject_cast<QGridLayout*>(layout())->addWidget(
                button,i%GRID_ROW_MAX, i/GRID_ROW_MAX, Qt::Alignment());
}


void IndicatorFLAGS::displayToFLAGS(const QStringList &flagslist)
{
    int i = 0;  // counter of current flagslist message
                // maybe less then defined in config.txt, but ordered
    int buttons_counter = 0;  // counter of button
    int buttons_size = m_bgroup->buttons().size();

    while(i<flagslist.size() && buttons_counter<buttons_size)
    {
        QString flag_message = flagslist[i];
        qDebug() << "input signal: FLAG = " << flag_message;

        while(buttons_counter<buttons_size)
        {
            FlagColorButton* button
                    = qobject_cast<FlagColorButton*>(m_bgroup->button(buttons_counter++));
            if(int state = button->getFlag()->changeState(flag_message); state >-1 ) {
                i++;        //flag_message соответствует текущему флагу(button)
                break;      //переход к следующему flag_message
            }
        }
    }

    while(buttons_counter<buttons_size)
    {
        FlagColorButton* button =
                qobject_cast<FlagColorButton*>(m_bgroup->button(buttons_counter++));
        button->getFlag()->setState(-1);
    }

}

