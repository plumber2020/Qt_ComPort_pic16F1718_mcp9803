#include "indicatorLCD.h"
#include "formSensor.h"

IndicatorLCD::IndicatorLCD(QWidget *parent) : QLCDNumber(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    setDecMode();
    setDigitCount(7);
    setSmallDecimalPoint(1);
    QString st = QString (
                "QLCDNumber {"
                    "background-color:rgb(200, 200, 250);"
                 "}");
    setStyleSheet(st);

    connect(qobject_cast<FormSensor*>(parent),&FormSensor::displayValue,
            [this](QString const& str){ display(str.toDouble()); });
}
