#ifndef INDICATORLCD_H
#define INDICATORLCD_H

#include <QLCDNumber>
#include <QWidget>

#define LCDNumber_DIGITCOUNT    7
#define LCDNumber_DECIMALPOINT  1
#define LCDNumber_STYLE         "QLCDNumber {"\
                                    "background-color: rgb(200, 200, 250);"\
                                "}"

class IndicatorLCD : public QLCDNumber
{
    Q_OBJECT
public:
    explicit IndicatorLCD(QWidget *parent = nullptr);

signals:
    //void displayToLCD(QString const&);
};

#endif // INDICATORLCD_H
