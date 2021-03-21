#include "flagElement.h"

FlagElement::FlagElement(QObject *parent) : QObject(parent){}

FlagElement::FlagElement(QStringList states, QObject *parent)
    : QObject(parent)
    , m_statesList(states)
{}

QString FlagElement::getFlagCurrentName() { return m_statesList[m_state]; }

unsigned FlagElement::getState() const { return m_state; }

void FlagElement::setState(const unsigned &state) { m_state = state; }

bool FlagElement::changeState(const QString &str)
{
    if (m_statesList[m_state] != str) {
        for (auto i=0; i<m_statesList.size(); ++i) {
            if (m_statesList[i] == str) {
                m_state = i;
                emit stateChanged(m_state);
                return true;
            }
        }
    }
    return false;
}
