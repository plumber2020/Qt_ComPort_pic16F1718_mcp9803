#ifndef FORMSENSOR_H
#define FORMSENSOR_H

#include <QWidget>
#include <QString>

enum IndicatorType {LCD, BAR };

namespace Ui {
class FormSensor;
}

class FormSensor : public QWidget
{
    Q_OBJECT
    IndicatorType m_indicatortype;
public:
    explicit FormSensor(IndicatorType indicatortype, QWidget *parent = nullptr);
    ~FormSensor();


signals:
    void displayValue(QString const&);
    void self_remove(QString);

public slots:

private slots:
    void on_pushButton_Close_clicked();

private:
    Ui::FormSensor *ui;
    QWidget *indicator;
};

#endif // FORMSENSOR_H
