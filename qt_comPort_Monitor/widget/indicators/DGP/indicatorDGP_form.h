#ifndef INDICATORDGP_FORM_H
#define INDICATORDGP_FORM_H

#include "./widget/indicator.h"
#include "qcustomplot.h"
#include <QWidget>
#include <QPair>

#define RANGE_X_MAXPOINTS 30

namespace Ui { class IndicatorDGP_Form; }

class IndicatorDGP_Form : public Indicator
{
    Q_OBJECT
    QString m_measure{}, m_unit{};
    double m_min{}, m_max{};

    struct Plot {
        QCustomPlot *customPlot;
        QVector<double> limits{};
    }
    m_plot;

public:
    explicit IndicatorDGP_Form(QWidget *parent = nullptr);
    ~IndicatorDGP_Form();

    // Indicator interface
public:
    void setParams(const QStringList &) override;
    void setValue(const QString &) override;

private:
    Ui::IndicatorDGP_Form *ui;
    void make_command(const QString &value);
};

#endif // INDICATORDGP_FORM_H
