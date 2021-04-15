#ifndef INDICATORFLG_FORM_H
#define INDICATORFLG_FORM_H

#include "./widget/indicator.h"
#include <QWidget>

namespace Ui { class IndicatorFLG_Form; }

class IndicatorFLG_Form : public Indicator
{
    Q_OBJECT
    int cuttent_state{-1};
    QStringList m_states{"0","1"};

public:
    explicit IndicatorFLG_Form(QWidget *parent = nullptr);
    ~IndicatorFLG_Form();

    // Indicator interface
public:
    void setParams(const QStringList &) override;
    void setValue(const QString &) override;

private:
    Ui::IndicatorFLG_Form *ui;
    void make_command(const QString &value);
};

#endif // INDICATORFLG_FORM_H
