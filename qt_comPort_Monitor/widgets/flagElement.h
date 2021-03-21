#ifndef FLAGELEMENT_H
#define FLAGELEMENT_H

#include <QObject>
#include <QString>
#include <QStringList>

class FlagElement : public QObject
{
    Q_OBJECT
   // Q_PROPERTY(unsigned m_state READ getState WRITE setState NOTIFY stateChanged)

    unsigned m_state{0};
    QStringList m_statesList{};
public:
    FlagElement(QObject *parent = nullptr);
    FlagElement(QStringList state, QObject *parent = nullptr);

    QString getFlagCurrentName();

    unsigned getState() const;
    void setState(const unsigned &state);

    bool changeState(QString const&);

signals:
    void stateChanged(unsigned);
};

#endif // FLAGELEMENT_H
