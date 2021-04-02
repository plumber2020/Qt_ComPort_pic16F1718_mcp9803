#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>

class Indicator : public QWidget
{
    Q_OBJECT
public:
    explicit Indicator(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual void setParams(QStringList const&){}
    virtual void setValues(QStringList const&){}
    virtual ~Indicator(){}
signals:
    void sendCommand(int);
};

#endif // INDICATOR_H
