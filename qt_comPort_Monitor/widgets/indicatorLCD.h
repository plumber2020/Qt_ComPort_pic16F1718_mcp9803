#ifndef INDICATORLCD_H
#define INDICATORLCD_H

#include <QLCDNumber>
#include <QWidget>

class IndicatorLCD : public QLCDNumber
{
    Q_OBJECT
public:
    explicit IndicatorLCD(QWidget *parent = nullptr);

signals:

};

#endif // INDICATORLCD_H
