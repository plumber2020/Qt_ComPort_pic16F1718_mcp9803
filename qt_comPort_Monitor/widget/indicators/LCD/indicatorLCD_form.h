#ifndef INDICATORLCD_FORM_H
#define INDICATORLCD_FORM_H

#include "./widget/indicator.h"

namespace Ui { class IndicatorLCD_Form; }

class IndicatorLCD_Form : public Indicator
{
    Q_OBJECT
    struct PARAM{
        QString measure, unit;
        int min, max;
    } m_param{};
public:
    explicit IndicatorLCD_Form(Indicator *parent = nullptr);
    ~IndicatorLCD_Form();

    // Indicator interface
public:
    void setParams(QStringList const&) override;
    void setValues(const QStringList &) override;

private:
    Ui::IndicatorLCD_Form *ui;
};

#endif // INDICATORLCD_FORM_H
