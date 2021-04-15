#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>

class Indicator : public QWidget
{
    Q_OBJECT
public:
    explicit Indicator(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual void setParams(QStringList const&){}
    virtual void setValue(QString const&){}
    virtual ~Indicator(){}
signals:
    void sendCommand(QString);

public:
    static Indicator *makeIndicator(QString indicatorName, QWidget *parent = nullptr);
};

#endif // INDICATOR_H
