#include "flagElement.h"

FlagElement::FlagElement(QObject *parent) : QObject(parent){}

FlagElement::FlagElement(QStringList states, QObject *parent)
    : QObject(parent)
    , m_statesList(states)
{
}

QString FlagElement::getFlagCurrentName() const {
    return (m_state<0)?QString("   "):(m_statesList[m_state]);
}

int FlagElement::getState() const { return m_state; }

void FlagElement::setState(int state) { m_state = state; emit stateChanged(m_state); }

bool FlagElement::contains(const QString &s)
{
    return m_statesList.contains(s);
}

bool FlagElement::isValid(int index)
{
    return index>-1 && index<m_statesList.size();
}

int FlagElement::maxState() const
{
    return m_statesList.size()-1;
}

int FlagElement::changeState(const QString &s)
{
    if (m_statesList.contains(s))
        setState(m_statesList.indexOf(s));
    else
        setState(-1);

    emit stateChanged(m_state);
    return getState();
}

int FlagElement::changeState(int index)
{
    if (isValid(index))
        setState(index);
    else
        setState(-1);

    emit stateChanged(m_state);
    return getState();
}
