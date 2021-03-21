#ifndef INDICATORFLAGS_H
#define INDICATORFLAGS_H

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
    QList<QPushButton*> m_buttonList;
    QButtonGroup *m_bgroup;

public:
    explicit IndicatorFLAGS(QWidget *parent = nullptr);
    IndicatorFLAGS(QString const& flags, QWidget *parent = nullptr);

signals:
    void commandFromFlagsButton(QString);

private slots:
    void selectionButtonChanges(int);
    void displayFlags(QString const&);

private:
    QStringList parseFlagsList(QString);
    QStringList parseFlagState(QString);
};

#endif // INDICATORFLAGS_H
