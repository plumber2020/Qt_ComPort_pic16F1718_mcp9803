#ifndef INDICATORFLAGS_H
#define INDICATORFLAGS_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QList>
#include <QPushButton>
#include <QButtonGroup>
#include <QString>
#include <QStringList>

#define GRID_ROW_MAX    2

class IndicatorFLAGS : public QGroupBox
{
    Q_OBJECT
//    QHash<QString,int> m_flagList;
    QButtonGroup *m_bgroup;

public:
    explicit IndicatorFLAGS(QWidget *parent = nullptr);
    void addFlagStates(QStringList const& flagStates);

signals:
    void commandFromFlags(QString);

public slots:
    void displayToFLAGS(QStringList const&);

};

#endif // INDICATORFLAGS_H
