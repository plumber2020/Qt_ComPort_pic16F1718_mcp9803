#ifndef FLAGELEMENT_H
#define FLAGELEMENT_H

#include <QObject>
#include <QString>
#include <QStringList>

class FlagElement : public QObject
{
    Q_OBJECT

    int m_state{-1};
    QStringList m_statesList{};
public:
    FlagElement(QObject *parent = nullptr);
    FlagElement(QStringList state, QObject *parent = nullptr);

    int getState() const;
    void setState(int state);
    bool contains(QString const&);
    bool isValid(int index);
    int maxState() const;
    int changeState(QString const&);
    int changeState(int);

    QString getFlagCurrentName() const;

signals:
    void stateChanged(int);
};

#endif // FLAGELEMENT_H
