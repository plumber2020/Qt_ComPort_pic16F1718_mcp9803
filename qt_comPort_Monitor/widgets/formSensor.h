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
    QString m_deviceName;
    IndicatorType m_indicatortype;
public:
    explicit FormSensor(QWidget *parent = nullptr);
    ~FormSensor();

    void addIndicator(QWidget* indicator);
    void setDeviceName(QString const& name);
    void setParameters(QString const& measure, QString const& unit);

signals:
    void displayValue(QString const&);
    void displayFlags(QString const&);
    void self_remove(QString);

public slots:
    void doFlagsCommand(QString const&);

private slots:
    void on_pushButton_Close_clicked();

private:
    Ui::FormSensor *ui;
    QWidget *indicator;
};

#endif // FORMSENSOR_H
