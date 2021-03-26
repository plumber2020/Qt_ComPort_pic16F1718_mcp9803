#include "indicatorBar.h"

IndicatorBar::IndicatorBar(QWidget *parent) : QProgressBar(parent)
{
    setOrientation(Qt::Vertical);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    setStyleSheet(ProgressBar_STYLE);
}
