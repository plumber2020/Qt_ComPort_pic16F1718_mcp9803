#include "indicatorLCD.h"

IndicatorLCD::IndicatorLCD(QWidget *parent) : QLCDNumber(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    setDecMode();
    setDigitCount(LCDNumber_DIGITCOUNT);
    setSmallDecimalPoint(LCDNumber_DECIMALPOINT);
    QString st = QString (LCDNumber_STYLE);
    setStyleSheet(st);
}
