#include "indicatorBar.h"
#include "formSensor.h"

IndicatorBar::IndicatorBar(QWidget *parent) : QProgressBar(parent)
{
    setOrientation(Qt::Vertical);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    QString st = QString (
                "QProgressBar::chunk {"
                    "background-color: #ff0000;"
                 "}");

    st.append("QProgressBar {"
                "border: 1px solid grey;"
                "border-radius: 2px;"
                "text-align: center;"
                "background: #eeeeee;"
              "}");
    setStyleSheet(st);

    connect(qobject_cast<FormSensor*>(parent),&FormSensor::displayValue,
            [this](QString const& str){ setValue(str.toInt()); });
}
