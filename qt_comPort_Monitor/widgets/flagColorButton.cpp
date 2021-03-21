#include "flagColorButton.h"


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

FlagElement *FlagColorButton::getFlagElement() const
{
    return m_flag;
}

void FlagColorButton::changeBackground(unsigned index)
{
    setText(m_flag->getFlagCurrentName());
    if(index)
        setBackground(QColor(Qt::BKGDCOLOR_PUSHBUTTON_ACTIVE));
    else
        restoreBackground();
}
