#ifndef INDICATORBAR_H
#define INDICATORBAR_H

#include <QWidget>
#include <QProgressBar>

class IndicatorBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit IndicatorBar(QWidget *parent = nullptr);

signals:

};

#endif // INDICATORBAR_H
