#ifndef INDICATORLCD_FORM_H
#define INDICATORLCD_FORM_H

#include "./widget/indicator.h"
#include <QWidget>

namespace Ui { class IndicatorLCD_Form; }

class IndicatorLCD_Form : public Indicator
{
    Q_OBJECT
    QList<double> limits{0.0,1.0};

public:
    explicit IndicatorLCD_Form(QWidget *parent = nullptr);
    ~IndicatorLCD_Form();

    // Indicator interface
public:
    void setParams(const QStringList &) override;
    void setValue(const QString &) override;

private:
    Ui::IndicatorLCD_Form *ui;
    void make_command(const QString &value);
};

#endif // INDICATORLCD_FORM_H
