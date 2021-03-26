#include "flagColorButton.h"


FlagElement *FlagColorButton::getFlag() const
{
    return m_flag;
}

bool FlagColorButton::contains(const QString &s)
{
    return m_flag->contains(s);
}

FlagColorButton::FlagColorButton(FlagElement *flag, QWidget *parent)
    : QPushButton(flag->getFlagCurrentName(), parent)
    , m_flag(flag)
{
    connect(flag,&FlagElement::stateChanged,
            this,&FlagColorButton::changeBackground);
}

QColor FlagColorButton::getBackground() const {
    return background;
}

void FlagColorButton::setBackground(const QColor &back) {
    currentground = background;
    //установка цвета фона через qss (таблица стилей qt)
    this->setStyleSheet(QString{"background-color: rgb(%1, %2, %3);"}
                        .arg(back.red()).arg(back.green()).arg(back.blue()));
}

void FlagColorButton::restoreBackground()
{
    //установка цвета фона через qss (таблица стилей qt)
    this->setStyleSheet(QString{"background-color: rgb(%1, %2, %3);"}
                        .arg(currentground.red()).arg(currentground.green()).arg(currentground.blue()));
}

void FlagColorButton::changeBackground(int index)
{
    setText(m_flag->getFlagCurrentName());
    if(index<0) {
        setText("IDLE");
        setBackground(QColor(BKGDCOLOR_PUSHBUTTON_DEFAULT));
        setEnabled(false);
        setFlat(true);
    } else {
        setEnabled(true);
        setFlat(false);
        if (index>0)
            setBackground(QColor(BKGDCOLOR_PUSHBUTTON_ACTIVE));
        else
            restoreBackground();
    }

}
