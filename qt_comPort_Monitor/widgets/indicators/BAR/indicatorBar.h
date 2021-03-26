#ifndef INDICATORBAR_H
#define INDICATORBAR_H

#include <QWidget>
#include <QProgressBar>

#define ProgressBar_STYLE           "QProgressBar {"                    \
                                        "border: 1px solid grey;"       \
                                        "border-radius: 2px;"           \
                                        "text-align: center;"           \
                                        "background: #eeeeee;"          \
                                    "}"                                 \
                                                                        \
                                    "QProgressBar::chunk {"             \
                                        "background-color: #ff0000;"    \
                                    "}"


class IndicatorBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit IndicatorBar(QWidget *parent = nullptr);

signals:

};

#endif // INDICATORBAR_H
