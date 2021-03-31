#ifndef INDICATOR_H
#define INDICATOR_H

#include <QObject>

class Indicator : public QObject
{
    Q_OBJECT
public:
    virtual void setParameters(QStringList const&) = 0;
    virtual ~Indicator(){}
signals:

public slots:
    virtual void display(QStringList const&) = 0;
};

#endif // INDICATOR_H
