#include "indicator.h"
#include "./widget/indicators/LCD/indicatorLCD_form.h"
#include "./widget/indicators/FLG/indicatorFLG_form.h"

Indicator* Indicator::makeIndicator(QString indicatorName, QWidget *parent)
{
    Indicator* indicator{nullptr};

    if(indicatorName=="LCD") indicator = new IndicatorLCD_Form(parent);
    else
    if(indicatorName=="FLG") indicator = new IndicatorFLG_Form(parent);

    return indicator;
}
